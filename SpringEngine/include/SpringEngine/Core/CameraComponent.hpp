#pragma once

#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	class ActorComponent;
	class SE_API CameraComponent : public SceneComponent
	{
	public:
		CameraComponent(ActorComponent* owner);
		virtual ~CameraComponent();

		glm::mat4 getViewProjection();
		glm::mat4 getProjection();
		glm::mat4 getView();
		void setRatio(float newRatio) { m_ratio = newRatio; };
	private:
		float m_ratio;
	};
}