#include <SpringEngine/Core/PointLightComponent.hpp>

namespace SE
{
	PointLightComponent::PointLightComponent(ActorComponent* owner) : LightComponent(owner), m_power(1.0f)
	{
		setName("Default point light");
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "Power", (void*)&m_power });
	}

	PointLightComponent::~PointLightComponent()
	{

	}
}