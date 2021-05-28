#pragma once

#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>

#include <SpringEngine/core.hpp>
#include <SpringEngine/Graphics/VertexArray.hpp>
#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Graphics/IndexBuffer.hpp>
#include <SpringEngine/Graphics/Framebuffer.hpp>
#include <SpringEngine/Core/LightComponent.hpp>
#include <SpringEngine/Core/PointLightComponent.hpp>
#include <SpringEngine/Core/DirectionalLightComponent.hpp>

namespace SE
{
	class Scene;
	class CameraComponent;
	class SE_API Renderer
	{
	public:
		//static void renderScene(Scene* scene, double deltaMillis);

		static void initDebugShaders();
		static void initSSAO(int samples);

		// API
		static void beginSceneDraw(CameraComponent* cam, Scene* scene);
		static int endSceneDraw();
		static void drawIndexed(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const Material* material, const glm::mat4* transform);
		static void Renderer::drawStripInstanced(size_t inputCount, size_t count, const Material* material, const glm::mat4* transform);
		static void Renderer::drawIndexedInstanced(size_t inputCount, size_t count, const unsigned int* indices, const Material* material, const glm::mat4* transform);

		static void Renderer::drawDebugNormals(const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const glm::mat4* transform, float drawLength = 1.0);

		static void Renderer::renderToScreen(Framebuffer* framebuffer);
		static void Renderer::deferredShadingDrawCall(Framebuffer* input, Framebuffer* output);

		static void Renderer::outlineSelectedObject(Framebuffer* input, Framebuffer* output, int selection);
		static void Renderer::drawDirectionalLightDepth(DirectionalLightComponent* light, const VertexArray* vertexArray, const IndexBuffer* indexBuffer, const glm::mat4* transform);

		static unsigned int getSceneDrawCalls() { return m_sceneDrawCalls; };
		static size_t getLightsNbr() { return m_sceneLights->size(); };

		static void setDebugIndex(int index) { m_debugIndex = index; };
		// API END
	private:
		static glm::mat4 m_VP;
		static glm::mat4 m_view;
		static glm::mat4 m_projection;
		static unsigned int m_sceneDrawCalls;
		static std::vector<LightComponent*>* m_sceneLights;
		static Shader* m_normalDebugShader;
		static Vector3f m_sceneCameraLocation;

		static Shader* m_screenShader;
		static VertexArray* m_screenVA;
		static VertexBuffer* m_screenVB;
		static VertexBufferLayout* m_screenVBL;
		static int m_debugIndex;

		static Shader* m_deferredShader;
		static Shader* m_outlineShader;
		static Shader* m_lightDepthShader;

		static int m_ssaoSamplesCount;
		static std::vector<glm::vec3> m_ssaoSamples;
		static int m_ssaoRandomsCount;
		static std::vector<glm::vec3> m_ssaoRandoms;
		static float m_ssaoDepth;
	};
}