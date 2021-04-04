#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Components/Mesh.hpp>

#include <SpringEngine/Misc/Macros.hpp>

#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	void Renderer::renderSceneElement(SceneElement* element)
	{
		element->getVertexArray()->bind();
		element->getIndexBuffer()->bind();
		element->getShader()->bind();

		GLCall(glDrawElements(GL_TRIANGLES, element->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr));

		element->getVertexArray()->unbind();
		element->getIndexBuffer()->unbind();
		element->getShader()->unbind();
	}

	void Renderer::renderScene(Scene* scene, double deltaMillis)
	{
		std::vector<std::shared_ptr<Component>>* components = scene->getComponents();
		Component* currentComp = nullptr;
		std::shared_ptr<Mesh> currentMesh=nullptr;
		float ratio = Application::get().getMainWindow().getRatio();
		glm::mat4 m_projectionMatrix = glm::perspective(glm::radians(60.f), ratio, 0.1f, 1000.0f);
		glm::mat4 m_viewMatrix = glm::lookAt(glm::vec3(scene->getViewCamera()->getPosition().x(), scene->getViewCamera()->getPosition().y(), scene->getViewCamera()->getPosition().z()), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
		glm::mat4 m_PV = m_projectionMatrix * m_viewMatrix;

		for (unsigned int i = 0; i < components->size(); i++)
		{
			//currentComp = i->get();
			currentMesh = std::static_pointer_cast<Mesh>((*components)[i]);
			float offset = 2.*std::sin(glfwGetTime());
			//currentMesh->setPosition(Vector3f(offset, 0.0, 0.0));
			currentMesh->addRotation(Vector3f(deltaMillis / 10., 0.0, 0.0));
			currentMesh->getVertexArray()->bind();
			currentMesh->getIndexBuffer()->bind();
			currentMesh->getMaterial()->bind();

			currentMesh->getMaterial()->updateShaderUniforms();
 			currentMesh->getMaterial()->getShader()->setUniformMat4f("u_projection", m_PV * *currentMesh->getModelMatrix());

			GLCall(glDrawElements(GL_TRIANGLES, currentMesh->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr));
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			currentMesh->getVertexArray()->unbind();
			currentMesh->getIndexBuffer()->unbind();
			currentMesh->getMaterial()->unbind();

		}
	}
}