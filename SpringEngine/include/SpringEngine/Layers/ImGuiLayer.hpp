#pragma once

#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Events/WindowEvents.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event& event) override;

		void begin();
		void end();

	private:
	};
}