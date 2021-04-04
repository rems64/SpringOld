#include <SpringEngine/Components/Actor.hpp>
#include <SpringEngine/Events/Event.hpp>

namespace SE
{
	Actor::Actor() : Component()
	{
	}

	Actor::~Actor()
	{
	}

	void Actor::onEvent(Event& ev)
	{
		if (ev.getEventType() != SE::EventType::MouseMoved)
		{
			SE_CORE_INFO("Event on world layer {0}", ev.toString());
		}
	}
}