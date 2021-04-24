#include <SpringEngine/Graphics/VertexBuffer.hpp>


namespace SE
{
	VertexBuffer::VertexBuffer()
	{
		GLCall(glCreateBuffers(1, &m_id));
	}

	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		GLCall(glGenBuffers(1, &m_id));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::VertexBuffer(const SE::VertexBuffer& src)
	{
		m_id = src.m_id;
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_id));
	}

	void VertexBuffer::setBuffer(const void* data, unsigned int size)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	}

	void VertexBuffer::setDynamicBuffer(const void* data, unsigned int size)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	void VertexBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	}

	void VertexBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}