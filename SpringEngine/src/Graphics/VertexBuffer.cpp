#include <SpringEngine/Graphics/VertexBuffer.hpp>

SE::VertexBuffer::VertexBuffer()
{
	GLCall(glCreateBuffers(1, &m_id));
}

SE::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

SE::VertexBuffer::VertexBuffer(const SE::VertexBuffer& src)
{
	m_id = src.m_id;
}

SE::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void SE::VertexBuffer::setBuffer(const void* data, unsigned int size)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void SE::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void SE::VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}