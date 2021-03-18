#include <SpringEngine/Core/SceneElement.hpp>


namespace SE
{
	SceneElement::SceneElement() : m_shader(new Shader("../../../ressources/shaders/basic.glsl"))
	{
		m_va = new VertexArray();
		m_vb = new VertexBuffer();
		m_ib = new IndexBuffer();
		m_vbl = new VertexBufferLayout();
		m_shader->compile();
		float vertices[9] = {
			0.0, 0.0, 0.0,
			1.0, 0.0, 0.0,
			0.5, 1.0, 0.0
		};

		unsigned int indices[3] = {
			0, 1, 2
		};
		m_vb->setBuffer(vertices, 9*sizeof(float));
		m_ib->setBuffer(indices, 3);
		m_vbl->Push<float>(3);

		m_va->bind();
		m_va->addBuffer(*m_vb, *m_vbl);
		m_va->unbind();
	}

	SceneElement::SceneElement(Vector3<float> position) : m_position(position), m_shader(new Shader("../../../ressources/shaders/basic.glsl"))
	{
		m_va = new VertexArray();
		m_vb = new VertexBuffer();
		m_ib = new IndexBuffer();
		m_vbl = new VertexBufferLayout();
	}

	SceneElement::~SceneElement()
	{
		delete m_va;
		delete m_vb;
		delete m_ib;
		delete m_vbl;
	}

	VertexArray* SceneElement::getVertexArray()
	{
		return m_va;
	}
	IndexBuffer* SceneElement::getIndexBuffer()
	{
		return m_ib;
	}
	Shader* SceneElement::getShader()
	{
		return m_shader;
	}
}