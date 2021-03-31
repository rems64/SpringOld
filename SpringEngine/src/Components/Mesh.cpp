#include <SpringEngine/Components/Mesh.hpp>

#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/core.hpp>

namespace SE
{
	//Mesh::Mesh() : m_va(), m_vb(), m_ib(), m_vbl(), m_shader("../../../../ISUFlightSimulator/ressources/test2.glsl")
	Mesh::Mesh() : m_va(), m_vb(), m_ib(), m_vbl(), m_material()
	{
	}

	Mesh::Mesh(const Mesh& src) : Component(src), m_va(src.m_va), m_ib(src.m_ib), m_vb(src.m_vb), m_vbl(src.m_vbl), m_material(src.m_material)
	{
		SE_CORE_INFO("Copying mesh...");
	}

	Mesh::~Mesh()
	{

	}

	Mesh& Mesh::operator=(Mesh other)
	{
		SE_CORE_INFO("Copying from operator=");
		m_isVisible = other.m_isVisible;
		m_position = other.m_position;
		m_scale = other.m_scale;
		m_rotation = other.m_rotation;
		m_parent = other.m_parent;
		m_components = other.m_components;
		m_material = other.m_material;
		return *this;
	}
}