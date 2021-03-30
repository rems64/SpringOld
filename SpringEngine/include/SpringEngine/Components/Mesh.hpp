#include <SpringEngine/Core/Component.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Graphics/Shader.hpp>
#include <SpringEngine/Graphics/VertexArray.hpp>
#include <SpringEngine/Graphics/VertexBuffer.hpp>
#include <SpringEngine/Graphics/IndexBuffer.hpp>
#include <SpringEngine/Graphics/VertexBufferLayout.hpp>

namespace SE
{
	class Mesh : public Component
	{
	public:
		Mesh();
		Mesh(const Mesh& src);
		Mesh& Mesh::operator=(Mesh other);
		~Mesh();

		Shader* getShader() { return &m_shader; };
		VertexArray* getVertexArray() { return &m_va; };
		VertexBuffer* getVertexBuffer() { return &m_vb; };
		IndexBuffer* getIndexBuffer() { return &m_ib; };
		VertexBufferLayout* getVertexBufferLayout() { return &m_vbl; };
	private:
		Shader m_shader;
		VertexArray m_va;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
		VertexBufferLayout m_vbl;
	};
}