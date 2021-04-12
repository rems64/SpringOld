#pragma once

#include <SpringEngine/Core/DataBlock.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Graphics/VertexArray.hpp>
#include <SpringEngine/Graphics/VertexBuffer.hpp>
#include <SpringEngine/Graphics/VertexBufferLayout.hpp>
#include <SpringEngine/Graphics/IndexBuffer.hpp>
#include <SpringEngine/Graphics/Material.hpp>

namespace SE
{
	class Scene;
	class SE_API Mesh : public DataBlock
	{
	public:
		Mesh();
		virtual ~Mesh();

		void setVertexArray(VertexArray* va) { m_va = va; };
		void setVertexBuffer(VertexBuffer* vb) { m_vb = vb; };
		void setVertexBufferLayout(VertexBufferLayout* vbl) { m_vbl = vbl; };
		void setIndexBuffer(IndexBuffer* ib) { m_ib = ib; };
		void setMaterial(Material* material) { m_material = material; };

		VertexArray* getVertexArray() { return m_va; };
		IndexBuffer* getIndexBuffer() { return m_ib; };
		Material* getMaterial() { return m_material; };
	private:
		VertexArray* m_va;
		VertexBuffer* m_vb;
		VertexBufferLayout* m_vbl;
		IndexBuffer* m_ib;
		Material* m_material;
	};
}