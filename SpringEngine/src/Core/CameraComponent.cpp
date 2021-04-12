#include <SpringEngine/Core/CameraComponent.hpp>

namespace SE
{
	CameraComponent::CameraComponent()
	{
	}

	CameraComponent::~CameraComponent()
	{
	}

	glm::mat4 CameraComponent::getViewProjection()
	{
		return glm::perspective(
			glm::radians(45.f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
			0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
			100.0f             // Far clipping plane. Keep as little as possible.
		) * glm::lookAt(
			glm::vec3(4, 3, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 1));
	}
}