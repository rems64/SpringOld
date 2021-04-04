#pragma once

#include <SpringEngine/Events/Event.hpp>

#include "../core.hpp"

namespace SE
{
	class SE_API Layer
	{
	public:
		Layer(const char* name = "Default layer");
		virtual ~Layer() = default;

		virtual void onEvent(SE::Event& event) {}

		virtual void onDetach() {}
		virtual void onAttach() {}

		virtual void onUpdate(double deltaTime) {}

		virtual void onImGuiRender() {}

		virtual void setBlockEvent(bool shouldBlock) { m_blockEvents = shouldBlock; };

	protected:
		bool m_enabled;
		bool m_blockEvents;
		const char* m_name;
	};
}