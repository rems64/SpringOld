#include <SpringEngine/Core/EditorCameraComponent.hpp>

namespace SE
{
	EditorCameraComponent::EditorCameraComponent(SceneComponent* owner) : CameraComponent(owner), m_yaw(0.0f), m_pitch(0.0f), m_distance(100.f), m_cameraTargetPoint(0.0, 0.0, 0.0)
	{

	}

	EditorCameraComponent::EditorCameraComponent(Actor* owner, bool root) : CameraComponent(owner, root), m_yaw(0.0f), m_pitch(0.0f), m_distance(100.f), m_cameraTargetPoint(0.0, 0.0, 0.0)
	{

	}

	EditorCameraComponent::~EditorCameraComponent()
	{

	}

	glm::mat4 EditorCameraComponent::getView()
	{
		m_location = m_cameraTargetPoint - getForward() * m_distance;
		return glm::inverse(glm::translate(glm::mat4(1.0f), m_location.getGlm()) * glm::toMat4(getOrientation()));
	}
}