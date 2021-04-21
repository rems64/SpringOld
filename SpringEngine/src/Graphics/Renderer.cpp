#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Core/CameraComponent.hpp>

#include <SpringEngine/Misc/Macros.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Core/Mesh.hpp>

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

	void Renderer::beginSceneDraw(CameraComponent* cam)
	{
		m_VP = cam->getViewProjection();
		m_view = cam->getView();
		m_sceneDrawCalls = 0;
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
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, NULL));
		material->unbindTextures();
		material->unbind();
		vertexArray->unbind();
		indexBuffer->unbind();
		m_sceneDrawCalls++;
	}

	void Renderer::drawStripInstanced(size_t inputCount, size_t count, const Material* material, const glm::mat4* transform)
	{
		material->bind();
		material->setProjectionMatrix(m_VP * (*transform));
		GLCall(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, inputCount, count));
		material->unbind();
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
	}
}