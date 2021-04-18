#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/RenderedComponent.hpp>

namespace SE
{
	Actor::Actor() : SpringObject()
	{
		setName("Default actor");
	}

	Actor::~Actor()
	{
	}

	void Actor::tick(double deltaSeconds)
	{
	}

	void Actor::drawCall()
	{
		for (std::vector<ActorComponent*>::iterator component = m_components.begin(); component != m_components.end(); component++)
		{
			RenderedComponent* renderedComponent = dynamic_cast<RenderedComponent*>(*component);
			if (renderedComponent)
			{
				renderedComponent->drawCall();
			}
		}
	}
}