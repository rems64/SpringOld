#pragma once

#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Input.hpp>

namespace SE
{
	class SE_API KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(KeyCode key) : m_keycode(key) {};

		EVENT_CLASS_TYPE(KeyPressed)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

		inline KeyCode getKeyCode() { return m_keycode; };

	private:
		KeyCode m_keycode;
	};
}