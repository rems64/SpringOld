#pragma once

#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/SceneElement.hpp>
#include <SpringEngine/Core/Scene.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{

	class SE_API WorldLayer : public Layer
	{
	public:
		WorldLayer();
		~WorldLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event & event) override;

		virtual void onUpdate(double deltaTime) override;

		virtual void onImGuiRender() override;

	private:
		Scene m_currentScene;
	};
}