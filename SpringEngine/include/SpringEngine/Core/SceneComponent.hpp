#pragma once

#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/Core/ActorComponent.hpp>

namespace SE
{
	class SE_API SceneComponent : public ActorComponent
	{
	public:
		SceneComponent();
		virtual ~SceneComponent();

		void setLocation(Vector3f& loc) { m_location = loc; };
		void setRotation(Vector3f& rot) { m_rotation = rot; };
		void setScale(Vector3f& scale) { m_scale = scale; };

		Vector3f getLocation() { return m_location; };
		Vector3f getRotation() { return m_rotation; };
		Vector3f getScale() { return m_scale; };

		void updateTransform();
		glm::mat4 getTransform() { return m_transform; };
	private:
		Vector3f m_location;
		Vector3f m_rotation;
		Vector3f m_scale;
		glm::mat4 m_transform;
	};
}