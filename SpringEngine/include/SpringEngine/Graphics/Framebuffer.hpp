#pragma once

#include <GL/glew.h>
#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Vector2.hpp>

namespace SE
{
	class SE_API Framebuffer
	{
	public:
		Framebuffer(Vector2<unsigned int> size);
		~Framebuffer();

		void invalidate();

		void bind();
		void unbind();

		uint32_t getColorAttachmentRendererID(uint32_t index = 0) const { return m_colorAttachment; };
		void resize(uint32_t width, uint32_t height);
		uint32_t getWidth() { return m_size.x(); };
		uint32_t getHeight() { return m_size.y(); };
		void clear(int value);

	private:
		uint32_t m_id;
		Vector2<unsigned int> m_size;

		uint32_t m_colorAttachment;
		uint32_t m_depthAttachment;
		uint32_t m_samples;
	};
}