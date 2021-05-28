#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/LightComponent.hpp>
#include <SpringEngine/Graphics/Framebuffer.hpp>

namespace SE
{
	class SE_API DirectionalLightComponent : public LightComponent
	{
	public:
		DirectionalLightComponent(SceneComponent* owner);
		virtual ~DirectionalLightComponent();

		float getPower() { return m_power; };
		void setPower(float power) { m_power = power; };

		virtual glm::mat4 getLightSpace() override;
		Framebuffer* getFramebuffer() const { return m_framebuffer;	};
		uint32_t getShadowMap() const { return m_framebuffer->getDepthAttachment(); };

	private:
		float m_power;
		Framebuffer* m_framebuffer;
		float m_nearClip;
		float m_farClip;
		float m_xMin;
		float m_xMax;
		float m_yMin;
		float m_yMax;
	};
}