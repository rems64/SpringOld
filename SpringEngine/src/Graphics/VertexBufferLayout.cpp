#include <SpringEngine/Graphics/VertexBufferLayout.hpp>

SE::VertexBufferLayout::VertexBufferLayout() : m_stride(0), m_elements(), m_countStride(0)
{
}

SE::VertexBufferLayout::VertexBufferLayout(const VertexBufferLayout& src) : m_countStride(src.m_countStride), m_stride(src.m_stride), m_elements()
{
	m_elements = src.m_elements;
}

SE::VertexBufferLayout& SE::VertexBufferLayout::operator=(const VertexBufferLayout& rhs)
{
	if (this != &rhs)
	{
		m_countStride = rhs.m_countStride;
		m_stride = rhs.m_stride;
		m_elements = rhs.m_elements;
	}
	return *this;
}


SE::VertexBufferLayout::~VertexBufferLayout()
{
}