#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Core/CameraComponent.hpp>

#include <SpringEngine/Misc/Macros.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Core/Mesh.hpp>
#include <SpringEngine/Core/PointLightComponent.hpp>
#include <SpringEngine/Core/DirectionalLightComponent.hpp>
#include <SpringEngine/Core/Math.hpp>

namespace SE
{
	glm::mat4 Renderer::m_VP                              = glm::mat4(1.0f);
	glm::mat4 Renderer::m_view                            = glm::mat4(1.0f);
	glm::mat4 Renderer::m_projection                      = glm::mat4(1.0f);
	unsigned int Renderer::m_sceneDrawCalls               = 0;
	Vector3f Renderer::m_sceneCameraLocation              = Vector3f(0.0, 0.0, 0.0);
	std::vector<LightComponent*>* Renderer::m_sceneLights = nullptr;
	Shader* Renderer::m_normalDebugShader                 = nullptr;
	Shader* Renderer::m_deferredShader                    = nullptr;
	VertexArray* Renderer::m_screenVA                     = nullptr;
	VertexBuffer* Renderer::m_screenVB                    = nullptr;
	VertexBufferLayout* Renderer::m_screenVBL             = nullptr;
	Shader* Renderer::m_screenShader                      = nullptr;
	int Renderer::m_debugIndex                            = 0;
	Shader* Renderer::m_outlineShader                     = nullptr;
	Shader* Renderer::m_lightDepthShader                  = nullptr;
	std::vector<glm::vec3> Renderer::m_ssaoSamples        = {};
	int Renderer::m_ssaoSamplesCount                      = 0;
	std::vector<glm::vec3> Renderer::m_ssaoRandoms        = {};
	int Renderer::m_ssaoRandomsCount                      = 0;
	float Renderer::m_ssaoDepth                           = 0.1f;

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

		m_deferredShader = new Shader("../../../../SpringEngine/shaders/deferred_pbr.glsl");
		m_deferredShader->compile();

		m_outlineShader = new Shader("../../../../ISUFlightSimulator/ressources/basic_outline.glsl");
		m_outlineShader->compile();

		m_lightDepthShader = new Shader("../../../../ISUFlightSimulator/ressources/basic_light_depth.glsl");
		m_lightDepthShader->compile();

		m_screenVA = new VertexArray();
		m_screenVB = new VertexBuffer();
		m_screenVB->setBuffer(screenShape, sizeof(screenShape));
		m_screenVBL = new VertexBufferLayout();
		m_screenVBL->Push<float>(2);
		m_screenVBL->Push<float>(2);
		m_screenVA->addBuffer(*m_screenVB, *m_screenVBL);
	}

	void Renderer::initSSAO(int samples)
	{
		SE_PROFILE_FUNCTION();
		m_ssaoSamplesCount = samples;
		m_ssaoSamples.resize((size_t)samples);
		for (size_t i = 0; i < samples; i++)
		{
			float scale = (float)i / samples;
			scale = lerp(scale * scale, 0.1, 1.0);
			m_ssaoSamples[i] = glm::normalize(glm::vec3(randomFloat()*2-1, randomFloat()*2-1, randomFloat())) * randomFloat() * scale;
		}
		m_ssaoRandomsCount = 8;
		m_ssaoRandoms.resize((size_t)m_ssaoRandomsCount);
		for (size_t i = 0; i < m_ssaoRandomsCount; i++)
		{
			m_ssaoRandoms[i] = glm::normalize(glm::vec3(randomFloat()*2-1, randomFloat()*2-1, 0.0));
		}
	}

	void Renderer::beginSceneDraw(CameraComponent* cam, Scene* scene)
	{
		m_VP = cam->getViewProjection();
		m_view = cam->getView();
		m_projection = cam->getProjection();
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

	void Renderer::deferredShadingDrawCall(Framebuffer* input, Framebuffer* output)
	{
		//GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, input->get()));
		//GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output->get()));
		//unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, attachments);

		//input->bindRead();
		output->bind();

		//GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_deferredShader->bind();
		m_screenVA->bind();

		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, input->getColorAttachmentRendererID(0)));
		m_deferredShader->setUniform1i("u_color", 0);
		GLCall(glActiveTexture(GL_TEXTURE1));
		GLCall(glBindTexture(GL_TEXTURE_2D, input->getColorAttachmentRendererID(1)));
		m_deferredShader->setUniform1i("u_normal", 1);
		GLCall(glActiveTexture(GL_TEXTURE2));
		GLCall(glBindTexture(GL_TEXTURE_2D, input->getColorAttachmentRendererID(2)));
		m_deferredShader->setUniform1i("u_position", 2);
		GLCall(glActiveTexture(GL_TEXTURE3));
		GLCall(glBindTexture(GL_TEXTURE_2D, input->getColorAttachmentRendererID(3)));
		m_deferredShader->setUniform1i("u_specular", 3);

		m_deferredShader->setUniform3f("u_cameraLocation_ws", m_sceneCameraLocation);
		for (uint32_t i = 0; i < m_sceneLights->size(); i++)
		{
			auto pointLight = dynamic_cast<PointLightComponent*>(m_sceneLights->at(i));
			if (pointLight)
			{
				char buffer[50];
				glm::vec4 loc = { pointLight->getLocation().getGlm(), 1.0 };
				auto tmp = pointLight->getParentTransform();
				loc = pointLight->getParentTransform() * loc;
				sprintf(buffer, "u_pointLights[%i].position", i);
				m_deferredShader->setUniform3f(buffer, loc.x, loc.y, loc.z);
				sprintf(buffer, "u_pointLights[%i].color", i);
				m_deferredShader->setUniform3f(buffer, pointLight->getColor().x(), pointLight->getColor().y(), pointLight->getColor().z());
				sprintf(buffer, "u_pointLights[%i].power", i);
				m_deferredShader->setUniform1f(buffer, pointLight->getPower());
			}
			auto directionalLight = dynamic_cast<DirectionalLightComponent*>(m_sceneLights->at(i));
			if (directionalLight)
			{
				glm::vec4 rot = { directionalLight->getRotation().getGlm(), 1.0 };
				rot = directionalLight->getParentTransform() * rot;
				glm::vec3 dir = glm::toMat4(glm::quat(rot)) * glm::vec4(0.0, 0.0, -1.0, 1.0);
				//SE_CORE_TRACE("x: {} y: {} z: {}", rot.x, rot.y, rot.z);
				m_deferredShader->setUniform3f("u_directionalLight.direction", dir.x, dir.y, dir.z);
				m_deferredShader->setUniform3f("u_directionalLight.color", directionalLight->getColor().x(), directionalLight->getColor().y(), directionalLight->getColor().z());
				m_deferredShader->setUniform1f("u_directionalLight.power", directionalLight->getPower());
				m_deferredShader->setUniformMat4f("u_directional_light_space", directionalLight->getLightSpace());
				GLCall(glActiveTexture(GL_TEXTURE4));
				GLCall(glBindTexture(GL_TEXTURE_2D, directionalLight->getShadowMap()));
				m_deferredShader->setUniform1i("directional_light_shadow_map", 4);
			}
		}
		char buffer[50];
		uint32_t i = 0;
		for (auto vector : m_ssaoSamples)
		{
			sprintf(buffer, "u_ssao_samples[%i]", i);
			m_deferredShader->setUniform3f(buffer, vector.x, vector.y, vector.z);
			i++;
		}
		i = 0;
		for (auto vector : m_ssaoRandoms)
		{
			sprintf(buffer, "u_ssao_randoms[%i]", i);
			m_deferredShader->setUniform3f(buffer, vector.x, vector.y, vector.z);
			i++;
		}
		m_deferredShader->setUniformMat4f("u_V", m_view);
		m_deferredShader->setUniformMat4f("u_P", m_projection);
		m_deferredShader->setUniformMat4f("u_VP", m_VP);
		GLCall(glActiveTexture(GL_TEXTURE5));
		GLCall(glBindTexture(GL_TEXTURE_2D, input->getDepthAttachment()));
		m_deferredShader->setUniform1i("u_camera_depth", 5);
		m_deferredShader->setUniform1f("u_ssao_depth ", m_ssaoDepth);


		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	}


	void Renderer::outlineSelectedObject(Framebuffer* input, Framebuffer* output, int selection)
	{
		output->bind();

		//GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));

		m_outlineShader->bind();
		m_screenVA->bind();

		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, input->getColorAttachmentRendererID(4)));
		m_outlineShader->setUniform1i("u_indices", 0);
		m_outlineShader->setUniform1i("u_index", selection);

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	}

	void Renderer::drawDirectionalLightDepth(DirectionalLightComponent* light, const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const glm::mat4* transform)
	{
		m_lightDepthShader->bind();
		m_lightDepthShader->setUniformMat4f("u_light_space", light->getLightSpace());
		m_lightDepthShader->setUniformMat4f("u_model_space", *transform);

		vertexArray->bind();
		indexBuffer->bind();
		//GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDisable(GL_BLEND));
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, NULL));
		vertexArray->unbind();
		indexBuffer->unbind();
		m_lightDepthShader->unbind();
	}
}