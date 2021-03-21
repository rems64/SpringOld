#include <SpringEngine/Core/Component.hpp>

namespace SE
{
	Component::Component() : SpringObject(), m_isVisible(true), m_position(0., 0., 0.), m_scale(1., 1., 1.), m_rotation(0., 0., 0.), m_parent(nullptr), m_components()
	{
	}

	Component::Component(const Component& src) : m_isVisible(src.m_isVisible), m_position(src.m_position), m_scale(src.m_scale), m_rotation(src.m_rotation), m_parent(src.m_parent), m_components(src.m_components)
	{
	}

	Component& Component::operator=(Component other)
	{
		m_isVisible = other.m_isVisible;
		m_position = other.m_position;
		m_scale = other.m_scale;
		m_rotation = other.m_rotation;
		m_parent = other.m_parent;
		m_components = other.m_components;
	}
}