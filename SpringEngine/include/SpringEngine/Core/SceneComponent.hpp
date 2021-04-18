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

		void setLocation(Vector3f& loc) { m_location = loc; updateTransform(); };
		void setRotation(Vector3f& rot) { m_rotation = rot; updateTransform(); };
		void setScale(Vector3f& scale) { m_scale = scale; updateTransform(); };

		void addLocation(Vector3f& loc) { m_location += loc; updateTransform(); };
		void addRotation(Vector3f& rot) { m_rotation += rot; updateTransform(); };
		void addScale(Vector3f& scale) { m_scale += scale; updateTransform(); };

		Vector3f getLocation() { return m_location; };
		Vector3f getRotation() { return m_rotation; };
		Vector3f getScale() { return m_scale; };

		virtual void updateTransform();
		virtual glm::mat4 getTransform() { return m_transform; };


	protected:
		virtual void onUpdateTransform();

		Vector3f m_location;
		Vector3f m_rotation;
		Vector3f m_scale;
		glm::mat4 m_transform;
	};
}