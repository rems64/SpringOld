#pragma once

#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>

#include <SpringEngine/core.hpp>
#include <SpringEngine/Graphics/VertexArray.hpp>
#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Graphics/IndexBuffer.hpp>
#include <SpringEngine/Core/LightComponent.hpp>
#include <SpringEngine/Core/PointLightComponent.hpp>

namespace SE
{
	class Scene;
	class CameraComponent;
	class SE_API Renderer
	{
	public:
		//static void renderScene(Scene* scene, double deltaMillis);

		// API
		static void beginSceneDraw(CameraComponent* cam, Scene* scene);
		static int endSceneDraw();
		static void drawIndexed(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const Material* material, const glm::mat4* transform);
		static void Renderer::drawStripInstanced(size_t inputCount, size_t count, const Material* material, const glm::mat4* transform);
		static void Renderer::drawIndexedInstanced(size_t inputCount, size_t count, const unsigned int* indices, const Material* material, const glm::mat4* transform);
		static unsigned int getSceneDrawCalls() { return m_sceneDrawCalls; };
		static unsigned int getLightsNbr() { return m_sceneLights->size(); };
		// API END
	private:
		static glm::mat4 m_VP;
		static glm::mat4 m_view;
		static unsigned int m_sceneDrawCalls;
		static std::vector<LightComponent*>* m_sceneLights;
	};
}