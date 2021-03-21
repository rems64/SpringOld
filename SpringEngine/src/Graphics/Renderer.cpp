#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Scene.hpp>

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

	void Renderer::renderScene(Scene* scene)
	{

	}
}