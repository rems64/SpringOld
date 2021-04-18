#include <SpringEngine/Core/CameraComponent.hpp>

namespace SE
{
	CameraComponent::CameraComponent() : SceneComponent()
	{
		setName("Default camera component");
	}

	CameraComponent::~CameraComponent()
	{
	}

	glm::mat4 CameraComponent::getViewProjection()
	{
		return glm::perspective(
			glm::radians(45.f),
			m_ratio,
			0.1f,
			100.0f
		) * glm::lookAt(
			m_location.getGlm(),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 1));
	}
}