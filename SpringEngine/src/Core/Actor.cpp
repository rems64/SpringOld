#include <SpringEngine/Core/Actor.hpp>

namespace SE
{
	Actor::Actor()
	{
	}

	Actor::~Actor()
	{
	}

	void Actor::tick(double deltaSeconds)
	{
		SE_CORE_TRACE("Tick");
	}
}