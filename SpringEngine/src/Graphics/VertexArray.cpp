#include <SpringEngine/Graphics/VertexArray.hpp>

SE::VertexArray::VertexArray() : m_id(0)
{
	GLCall(glCreateVertexArrays(1, &m_id));
}

SE::VertexArray::VertexArray(const VertexArray& src) : m_id(0)
{
	m_id = src.m_id;
}

SE::VertexArray& SE::VertexArray::operator=(const SE::VertexArray& rhs)
{
	m_id = rhs.m_id;
	return *this;
}

SE::VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void SE::VertexArray::addBuffer(const SE::VertexBuffer& vb, const SE::VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void SE::VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_id));
}

void SE::VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}

int SE::VertexArray::getId()
{
	return m_id;
}
