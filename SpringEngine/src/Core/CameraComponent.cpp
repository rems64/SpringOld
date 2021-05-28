#include <SpringEngine/Core/CameraComponent.hpp>

namespace SE
{
	CameraComponent::CameraComponent(SceneComponent* owner) : SceneComponent(owner), m_ratio(1.0f)
	{
		setName("Default camera component");
	}

	CameraComponent::CameraComponent(Actor* owner, bool root) : SceneComponent(owner, root), m_ratio(1.0f)
	{
	}

	CameraComponent::~CameraComponent()
	{
	}

	glm::mat4 CameraComponent::getViewProjection()
	{
		return getProjection() * getView();
	}

	glm::mat4 CameraComponent::getView()
	{
		//return glm::lookAt(
		//	m_location.getGlm(),
		//	glm::vec3(0, 0, 0),
		//	glm::vec3(0, 0, 1));
		//return glm::inverse(getLocalTransform());

		//return glm::inverse(glm::translate(glm::toMat4(glm::quat(m_rotation.getGlm())), m_location.getGlm()));

		return glm::inverse(getTransform());
	}

	glm::mat4 CameraComponent::getProjection()
	{
		return glm::perspective(
			glm::radians(30.f),
			m_ratio,
			0.1f,
			1000.0f
		);
	}
}