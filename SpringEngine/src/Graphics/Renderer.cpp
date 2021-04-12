#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>

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

	glm::mat4 Renderer::m_VP = glm::mat4();
	unsigned int Renderer::m_sceneDrawCalls = 0;

	void Renderer::beginSceneDraw(Scene* scene)
	{
		m_VP = scene->getMainCamera()->getViewProjection();
		m_sceneDrawCalls = 0;
	}

	int Renderer::endSceneDraw()
	{
		return 0;
	}

	void Renderer::drawIndexed(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const Material* material, const glm::mat4* transform)
	{
		vertexArray->bind();
		indexBuffer->bind();
		material->bind();
		material->setTransformMatrix(m_VP);
		material->bindTextures();
		GLCall(glDrawElements(GL_TRIANGLES, m_ib->getCount(), GL_UNSIGNED_INT, NULL));
		material->unbind();
		vertexArray->unbind();
		indexBuffer->unbind();
	}
}