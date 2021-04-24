#include <SpringEngine/Core/ActorComponent.hpp>

namespace SE
{
	ActorComponent::ActorComponent() : SpringObject(), m_components(), m_owner(nullptr)
	{

	}
	ActorComponent::ActorComponent(ActorComponent* owner) : SpringObject(), m_components(), m_owner(owner)
	{
		setName("Default actor component");
	}

	ActorComponent::~ActorComponent()
	{
	}

	void ActorComponent::destroy()
	{
		getOwner()->removeComponent(this);
		for (auto component : m_components)
		{
			m_owner->addComponent<ActorComponent>(component);
			component->setOwner(m_owner);
		}
		postDestroy();
		delete this;
	}
}