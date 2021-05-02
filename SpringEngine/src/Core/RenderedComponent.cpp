#include <SpringEngine/Core/RenderedComponent.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/Scene.hpp>

namespace SE
{
	RenderedComponent::RenderedComponent(ActorComponent* owner) : SceneComponent(owner)
	{
	}

	RenderedComponent::~RenderedComponent()
	{
	}

	void RenderedComponent::postDestroy()
	{
		getActorOwner()->getScene()->unregisterRenderedComponent(this);
	}
}