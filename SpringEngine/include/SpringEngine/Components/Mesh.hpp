#include <SpringEngine/Core/Component.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Graphics/Material.hpp>
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

		void setMaterial(Material* material) { m_material = material; };
		Material* getMaterial() { return m_material; };
		VertexArray* getVertexArray() { return &m_va; };
		VertexBuffer* getVertexBuffer() { return &m_vb; };
		IndexBuffer* getIndexBuffer() { return &m_ib; };
		VertexBufferLayout* getVertexBufferLayout() { return &m_vbl; };
	private:
		Material* m_material;
		VertexArray m_va;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
		VertexBufferLayout m_vbl;
	};
}