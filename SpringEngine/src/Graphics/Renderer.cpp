#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Components/Mesh.hpp>

#include <SpringEngine/Misc/Macros.hpp>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

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
		glm::mat4 m_projectionMatrix = glm::perspective(glm::radians(60.f), 640.f/480.f, 0.1f, 1000.0f);
		glm::mat4 m_viewMatrix = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
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
			currentMesh->getShader()->bind();

			//currentMesh->getShader()->setUniformMat4f("u_projection", m_PV * (*currentMesh->getModelMatrix()));
			//currentMesh->getShader()->setUniformMat4f("u_modelprojection", m_projectionMatrix);
			//currentMesh->getShader()->setUniformMat4f("u_viewprojection", m_viewMatrix);
			//currentMesh->getShader()->setUniform3f("u_lightposition", 0.f, 2.f, 0.f);

			currentMesh->getShader()->setUniformMat4f("model", *currentMesh->getModelMatrix());
			currentMesh->getShader()->setUniformMat4f("view", m_viewMatrix);
			currentMesh->getShader()->setUniformMat4f("projection", m_projectionMatrix);

			currentMesh->getShader()->setUniform3f("lightPos", 1.2f, 1.0f, 2.0f);
			currentMesh->getShader()->setUniform3f("lightColor", 1.f, 1.f, 1.f);
			currentMesh->getShader()->setUniform3f("objectColor", 1.f, 1.f, 1.f);

			GLCall(glDrawElements(GL_TRIANGLES, currentMesh->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr));
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			currentMesh->getVertexArray()->unbind();
			currentMesh->getIndexBuffer()->unbind();
			currentMesh->getShader()->unbind();

		}
	}
}