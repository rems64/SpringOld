#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Core/CameraComponent.hpp>

#include <SpringEngine/Misc/Macros.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Core/Mesh.hpp>
#include <SpringEngine/Core/PointLightComponent.hpp>

namespace SE
{
	/*
	void Renderer::renderScene(Scene* scene, double deltaMillis)
	{
		std::vector<unsigned int> actors = *scene->getRegisteredActors();
		for (unsigned int i = 0; i < actors.size(); i++)
		{
			Mesh* mesh = Application::get().getDataManager()->getRegisteredMesh(actors[i]);
			mesh->drawCall(scene);
		}
	}
	*/

	glm::mat4 Renderer::m_VP = glm::mat4(1.0f);
	glm::mat4 Renderer::m_view = glm::mat4(1.0f);
	unsigned int Renderer::m_sceneDrawCalls = 0;
	Vector3f Renderer::m_sceneCameraLocation = Vector3f(0.0, 0.0, 0.0);
	std::vector<LightComponent*>* Renderer::m_sceneLights = nullptr;
	Shader* Renderer::m_normalDebugShader = nullptr;
	VertexArray* Renderer::m_screenVA = nullptr;
	VertexBuffer* Renderer::m_screenVB = nullptr;
	VertexBufferLayout* Renderer::m_screenVBL = nullptr;
	Shader* Renderer::m_screenShader = nullptr;
	int Renderer::m_debugIndex = 0;

	float screenShape[24] = {
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};


	void Renderer::initDebugShaders()
	{
		m_normalDebugShader = new Shader("../../../../ISUFlightSimulator/ressources/basic_normal_debug.glsl");
		m_normalDebugShader->compile();

		m_screenShader = new Shader("../../../../ISUFlightSimulator/ressources/screen.glsl");
		m_screenShader->compile();

		m_screenVA = new VertexArray();
		m_screenVB = new VertexBuffer();
		m_screenVB->setBuffer(screenShape, sizeof(screenShape));
		m_screenVBL = new VertexBufferLayout();
		m_screenVBL->Push<float>(2);
		m_screenVBL->Push<float>(2);
		m_screenVA->addBuffer(*m_screenVB, *m_screenVBL);
	}

	void Renderer::beginSceneDraw(CameraComponent* cam, Scene* scene)
	{
		m_VP = cam->getViewProjection();
		m_view = cam->getView();
		m_sceneDrawCalls = 0;
		m_sceneLights = scene->getLights();
		m_sceneCameraLocation = cam->getLocation();
	}

	int Renderer::endSceneDraw()
	{
		return m_sceneDrawCalls;
	}

	void Renderer::drawIndexed(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const Material* material, const glm::mat4* transform)
	{
		glDisable(GL_BLEND);
		vertexArray->bind();
		indexBuffer->bind();
		material->bind();
		material->setProjectionMatrix(m_VP * (*transform));
		material->bindTextures();
		material->getShader()->setUniform3f("u_camera_location", m_sceneCameraLocation);
		for (uint32_t i=0; i<m_sceneLights->size(); i++)
		{
			auto pointLight = dynamic_cast<PointLightComponent*>(m_sceneLights->at(i));
			if (pointLight)
			{
				char buffer[50];
				glm::vec4 loc = { pointLight->getLocation().getGlm(), 1.0 };
				auto tmp = pointLight->getParentTransform();
				loc = pointLight->getParentTransform() * loc;
				sprintf(buffer, "pointLights[%i].position", i);
				material->getShader()->setUniform3f(buffer, loc.x, loc.y, loc.z);
				sprintf(buffer, "pointLights[%i].color", i);
				material->getShader()->setUniform3f(buffer, pointLight->getColor().x(), pointLight->getColor().y(), pointLight->getColor().z());
				sprintf(buffer, "pointLights[%i].power", i);
				material->getShader()->setUniform1f(buffer, pointLight->getPower());
			}
		}


		//material->setViewMatrix(m_view);

		material->setModelMatrix(*transform);
		material->getShader()->setUniform1i("u_index", m_debugIndex);
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, NULL));
		material->unbindTextures();
		material->unbind();
		vertexArray->unbind();
		indexBuffer->unbind();
		m_sceneDrawCalls++;
	}

	void Renderer::drawDebugNormals(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const glm::mat4* transform, float drawLength)
	{
		vertexArray->bind();
		indexBuffer->bind();
		m_normalDebugShader->bind();
		m_normalDebugShader->setUniformMat4f("u_projection", m_VP * (*transform));
		m_normalDebugShader->setUniform1f("u_normal_length", drawLength);
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, NULL));
		m_normalDebugShader->unbind();
		vertexArray->unbind();
		indexBuffer->unbind();
		
	}

	void Renderer::drawStripInstanced(size_t inputCount, size_t count, const Material* material, const glm::mat4* transform)
	{
		material->bind();
		material->setProjectionMatrix(m_VP * (*transform));
		GLCall(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, inputCount, count));
		material->unbind();
		m_sceneDrawCalls++;
	}

	void Renderer::drawIndexedInstanced(size_t inputCount, size_t count, const unsigned int* indices, const Material* material, const glm::mat4* transform)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		material->bind();
		material->setProjectionMatrix(m_VP * (*transform));
		material->setViewMatrix(m_view);
		GLCall(glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, indices, inputCount));
		material->unbind();
		m_sceneDrawCalls++;
	}

	void Renderer::renderToScreen(Framebuffer* framebuffer)
	{
		glDisable(GL_DEPTH_TEST);
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_screenShader->bind();
		m_screenVA->bind();
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, framebuffer->getColorAttachmentRendererID(0)));
		m_screenShader->setUniform1i("u_framebuffer", 0);

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	}
}