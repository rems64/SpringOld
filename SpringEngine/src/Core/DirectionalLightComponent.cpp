#include <SpringEngine/Core/DirectionalLightComponent.hpp>

namespace SE
{
	DirectionalLightComponent::DirectionalLightComponent(SceneComponent* owner) : LightComponent(owner), m_framebuffer(new Framebuffer(SE::Vector2d(2048, 2048), {})), m_nearClip(1.0f), m_farClip(10.0f), m_xMin(-10.0f), m_xMax(10.0f), m_yMin(-10.0f), m_yMax(10.0f), m_power(1.0)
	{
		setName("Default directional light");
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "Power", (void*)&m_power, 0.001f });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "Near clip", (void*)&m_nearClip, 0.001f });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "Far clip", (void*)&m_farClip, 0.001f });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "X min", (void*)&m_xMin, 0.001f });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "X max", (void*)&m_xMax, 0.001f });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "Y min", (void*)&m_yMin, 0.001f });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::FloatInput, "Y max", (void*)&m_yMax, 0.001f });
		//setRotation(Vector3f(glm::radians(90.0f), 0.0, 0.0));
	}

	DirectionalLightComponent::~DirectionalLightComponent()
	{

	}

	glm::mat4 DirectionalLightComponent::getLightSpace()
	{
		glm::mat4 lightProjection = glm::ortho(m_xMin, m_xMax, m_yMin, m_yMax, m_nearClip, m_farClip);
		//return lightProjection * glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, far_plane / 2)) * glm::toMat4(glm::quat(m_rotation.getGlm())));// * glm::inverse(getTransform());
		//return lightProjection * glm::lookAt(glm::vec3(4.0, 4.0, 4.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
		//return lightProjection * glm::lookAt(glm::vec3(glm::quat(getWorldRotation().getGlm()) * glm::vec4(0.0, 0.0, m_farClip / 2, 1.0)), getWorldLocation().getGlm(), glm::vec3(0, 1, 0));
		return lightProjection * glm::lookAt(glm::vec3(getTransform() * glm::vec4(0.0, 0.0, m_farClip / 2, 1.0)), getWorldLocation().getGlm(), glm::vec3(0, 1, 0));
	}
}