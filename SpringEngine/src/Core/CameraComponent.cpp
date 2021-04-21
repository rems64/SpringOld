#include <SpringEngine/Core/CameraComponent.hpp>

namespace SE
{
	CameraComponent::CameraComponent(ActorComponent* owner) : SceneComponent(owner), m_ratio(1.0f)
	{
		setName("Default camera component");
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
		return glm::lookAt(
			m_location.getGlm(),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 1));
	}

	glm::mat4 CameraComponent::getProjection()
	{
		return glm::perspective(
			glm::radians(30.f),
			m_ratio,
			0.1f,
			100.0f
		);
	}
}