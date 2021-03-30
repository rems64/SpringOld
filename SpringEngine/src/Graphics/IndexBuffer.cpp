#include <SpringEngine/Graphics/IndexBuffer.hpp>

#include <SpringEngine/Misc/Logger.hpp>

SE::IndexBuffer::IndexBuffer() : m_count(0)
{
	GLCall(glGenBuffers(1, &m_id));
}

SE::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
}

SE::IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void SE::IndexBuffer::setBuffer(const void* data, unsigned int count)
{
	m_count = count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
}

void SE::IndexBuffer::setBuffer(const unsigned long* data, unsigned int count)
{
	m_count = count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned long), data, GL_STATIC_DRAW))
}

void SE::IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void SE::IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void SE::IndexBuffer::debugPrint() const
{
	auto ptr = glMapBufferRange(m_id, 0, 1, GL_MAP_READ_BIT);
	//std::cout << ptr << std::endl;
	SE_CORE_INFO("Debug print {0}", ptr);
}