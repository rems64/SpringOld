#include <SpringEngine/Core/Mesh.hpp>

namespace SE
{
	Mesh::Mesh() : DataBlock(), m_va(), m_vb(), m_vbl(), m_ib(), m_material()
	{
		m_isValid = false;
	}

	Mesh::~Mesh()
	{
		delete m_va;
		delete m_vb;
		delete m_vbl;
		delete m_ib;
		delete m_material;
	}
}