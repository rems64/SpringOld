#include <SpringEngine/Core/ActorComponent.hpp>

namespace SE
{
	ActorComponent::ActorComponent() : SpringObject(), m_components()
	{
		setName("Default actor component");
	}

	ActorComponent::~ActorComponent()
	{
	}
}