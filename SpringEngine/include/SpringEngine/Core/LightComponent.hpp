#pragma once
#include <SpringEngine/Core/SceneComponent.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/core.hpp>
#include <SpringEngine/Editor/EditorEditable.hpp>

namespace SE
{
	class SE_API LightComponent : public SceneComponent, public EditorEditable
	{
	public:
		LightComponent(SceneComponent* owner);
		virtual ~LightComponent();

		Vector3f& getColor() { return m_color; };
		void setColor(Vector3f color) { m_color = color; };

		virtual void postDestroy() override;

		virtual glm::mat4 getLightSpace() { return glm::mat4(1.0f); };

	private:
		Vector3f m_color;
	};
}