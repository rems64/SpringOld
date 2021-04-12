#pragma once

#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>

#include <SpringEngine/core.hpp>
#include <SpringEngine/Graphics/VertexArray.hpp>
#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Graphics/IndexBuffer.hpp>

namespace SE
{
	class Scene;
	class SE_API Renderer
	{
	public:
		//static void renderScene(Scene* scene, double deltaMillis);

		// API
		static void beginSceneDraw(Scene* scene);
		static int endSceneDraw();
		static void drawIndexed(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const Material* material, const glm::mat4* transform);
		// API END
	private:
		static glm::mat4 m_VP;
		static unsigned int m_sceneDrawCalls;
	};
}