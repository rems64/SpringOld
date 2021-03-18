#pragma once

#include <SpringEngine/Core/Component.hpp>

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <SpringEngine/Core/Vector3.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API CameraComponent : public Component
	{
	public:
		CameraComponent();
		~CameraComponent();

	private:
		glm::mat4 m_projection;
	};
}