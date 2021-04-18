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
		void setRatio(float newRatio) { m_ratio = newRatio; };
	private:
		float m_ratio;
	};
}