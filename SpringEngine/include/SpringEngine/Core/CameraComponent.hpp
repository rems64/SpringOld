#pragma once

#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	class SE_API CameraComponent : public SceneComponent
	{
	public:
		CameraComponent();
		virtual ~CameraComponent();

		glm::mat4 getViewProjection();
	private:

	};
}