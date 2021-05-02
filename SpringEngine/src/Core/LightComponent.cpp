#include <SpringEngine/Core/LightComponent.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/Scene.hpp>

namespace SE
{
	LightComponent::LightComponent(ActorComponent* owner) : SceneComponent(owner), m_color(1.0f, 1.0f, 1.0f)
	{
		setName("Default light");
	}

	LightComponent::~LightComponent()
	{
	}

	void LightComponent::postDestroy()
	{
		getActorOwner()->getScene()->unregisterLight(this);
	}
}