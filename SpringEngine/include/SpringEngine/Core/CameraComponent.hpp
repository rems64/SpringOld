#pragma once

#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	class ActorComponent;
	class SE_API CameraComponent : public SceneComponent
	{
	public:
		CameraComponent(SceneComponent* owner);
		CameraComponent(Actor* owner, bool root);
		virtual ~CameraComponent();

		glm::mat4 getViewProjection();
		virtual glm::mat4 getProjection();
		virtual glm::mat4 getView();
		void setRatio(float newRatio) { m_ratio = newRatio; };
		void setViewport(float width, float height)
		{
			m_viewportWidth = width;
			m_viewportHeight = height;
		}
	protected:
		float m_ratio;
		float m_viewportWidth;
		float m_viewportHeight;
	};
}