#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/RenderedComponent.hpp>
#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	Actor::Actor() : SpringObject(), m_rootComponent(), isPendingKill(false)
	{
		setName("Default actor");
		m_rootComponent = new SceneComponent(this, true);
		m_rootComponent->setName("Default actor root");
	}

	Actor::~Actor()
	{
	}

	void Actor::onEvent(Event& ev)
	{

	}

	void Actor::editorUpdate(double deltaSeconds)
	{
		for (auto component : *m_rootComponent->getComponents())
		{
			component->editorUpdate(deltaSeconds);
		}
	}

	void Actor::update(double deltaSeconds)
	{
		for (auto component : *m_rootComponent->getComponents())
		{
			component->update(deltaSeconds);
		}
	}

	uint32_t Actor::getComponentCount()
	{
		return m_rootComponent->getComponentCount();
	}

	void Actor::drawCall()
	{
		for (std::vector<ActorComponent*>::iterator component = m_rootComponent->getComponents()->begin(); component != m_rootComponent->getComponents()->end(); component++)
		{
			RenderedComponent* renderedComponent = dynamic_cast<RenderedComponent*>(*component);
			if (renderedComponent)
			{
				renderedComponent->drawCall();
			}
		}
	}
}