#include <SpringEngine/Core/Component.hpp>

#include <SpringEngine/Misc/Logger.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SE
{
	Component::Component() : m_isVisible(true), m_position(0., 0., 0.), m_scale(1., 1., 1.), m_rotation(0., 0., 0.), m_parent(nullptr), m_components()
	{
		updateModelMatrix();
	}

	Component::Component(const Component& src) : m_isVisible(src.m_isVisible), m_position(src.m_position), m_scale(src.m_scale), m_rotation(src.m_rotation), m_parent(src.m_parent), m_components(src.m_components)
	{
		SE_CORE_WARN("Copying component....");
	}

	Component& Component::operator=(Component other)
	{
		m_isVisible = other.m_isVisible;
		m_position = other.m_position;
		m_scale = other.m_scale;
		m_rotation = other.m_rotation;
		m_parent = other.m_parent;
		m_components = other.m_components;
		return *this;
	}

	void Component::updateModelMatrix()
	{
		m_modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(m_position.x(), m_position.y(), m_position.z())) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x()), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y()), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z()), glm::vec3(0, 0, 1));
	}
}