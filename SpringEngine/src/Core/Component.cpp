#include <SpringEngine/Core/Component.hpp>

namespace SE
{
	Component::Component() : SpringObject(), m_isVisible(true), m_position(0., 0., 0.), m_scale(1., 1., 1.), m_rotation(0., 0., 0.)
	{
	}
}