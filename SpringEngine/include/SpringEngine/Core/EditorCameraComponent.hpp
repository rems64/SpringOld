#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/CameraComponent.hpp>


class EditorCamera;
namespace SE
{
	class SE_API EditorCameraComponent : public CameraComponent
	{
	public:
		EditorCameraComponent(ActorComponent* owner);
		EditorCameraComponent(Actor* owner, bool root);
		~EditorCameraComponent();

		friend EditorCamera;

		virtual glm::mat4 getView() override;
		virtual glm::quat getOrientation() override { return glm::quat(glm::vec3(-m_pitch, -m_yaw, 0.0f)); };
		virtual Vector3f getForward() override { return Vector3f(glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f))); };
	private:
		float m_yaw;
		float m_pitch;
		float m_distance;
		Vector3f m_cameraTargetPoint;
	};
}