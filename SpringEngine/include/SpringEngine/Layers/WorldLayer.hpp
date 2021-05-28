#pragma once

#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Graphics/Framebuffer.hpp>
#include <SpringEngine/Graphics/Shader.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{

	class SE_API WorldLayer : public Layer
	{
	public:
		WorldLayer();
		virtual ~WorldLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event & event) override;

		virtual void onUpdate(double deltaTime) override;

		virtual void onImGuiRender() override;

		Scene* getScene() { return m_currentScene.get(); }

	private:
		std::shared_ptr<Scene> m_currentScene;
		SE::Vector2f m_viewport;
		SE::Framebuffer* m_framebuffer;
	};
}