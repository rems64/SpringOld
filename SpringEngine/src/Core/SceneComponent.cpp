#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	SceneComponent::SceneComponent() : m_location(0.0, 0.0, 0.0), m_rotation(0.0, 0.0, 0.0), m_scale(1.0, 1.0, 1.0), m_transform()
	{
		updateTransform();
	}

	SceneComponent::~SceneComponent()
	{
	}

	void SceneComponent::updateTransform()
	{
		m_transform = glm::mat4(1.0f);
		m_transform = glm::translate(m_transform, m_location.getGlm());
		m_transform = glm::rotate(m_transform, m_rotation.z(), glm::vec3(0, 0, 1));
		m_transform = glm::scale(m_transform, m_scale.getGlm());
		onUpdateTransform();
	}

	void SceneComponent::onUpdateTransform()
	{
	}
}