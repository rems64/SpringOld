#pragma once
#include <SpringEngine/Core/SceneComponent.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API LightComponent : public SceneComponent
	{
	public:
		LightComponent(ActorComponent* owner);
		~LightComponent();

		Vector3f& getColor() { return m_color; };
		void setColor(Vector3f color) { m_color = color; };

		virtual void postDestroy() override;

	private:
		Vector3f m_color;
	};
}