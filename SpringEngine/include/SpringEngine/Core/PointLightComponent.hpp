#pragma once
#include <SpringEngine/Core/LightComponent.hpp>
#include <SpringEngine/Editor/EditorEditable.hpp>

namespace SE
{
	class SE_API PointLightComponent : public LightComponent
	{
	public:
		PointLightComponent(SceneComponent* owner);
		~PointLightComponent();

		float getPower() { return m_power; };
		void setPower(float power) { m_power = power; };
	private:
		float m_power;
	};
}