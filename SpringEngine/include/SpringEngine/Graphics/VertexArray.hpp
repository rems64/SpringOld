#pragma once

#include <GL/glew.h>
#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Graphics/VertexBuffer.hpp>
#include <SpringEngine/Graphics/VertexBufferLayout.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API VertexArray
	{
	public:
		VertexArray();
		VertexArray(const VertexArray&);
		VertexArray& operator=(const VertexArray& rhs);
		~VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

		int getId();

	private:
		unsigned int m_id;
	};
}