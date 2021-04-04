#pragma once

#include <SpringEngine/Core/Component.hpp>

namespace SE
{
	class Event;
	class Actor : public Component
	{
	public:
		Actor();
		~Actor();

		void onEvent(Event& ev);
	private:

	};
}