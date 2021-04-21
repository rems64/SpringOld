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
		postDestroy();
		delete this;
	}
}