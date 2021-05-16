#include <SpringEngine/Graphics/Framebuffer.hpp>

namespace SE
{
	Framebuffer::Framebuffer(Vector2<unsigned int> size) : m_id(0), m_size(size), m_samples(16)
	{
		invalidate();
	}

	Framebuffer::~Framebuffer()
	{
		GLCall(glDeleteFramebuffers(1, &m_id));
		GLCall(glDeleteTextures(2, m_colorAttachment.data()));
		GLCall(glDeleteTextures(1, &m_depthAttachment));
	}

	void Framebuffer::invalidate()
	{
		uint32_t number = 2;
		m_colorAttachment.resize(number);
		if (m_size.x() == 0 || m_size.y() == 0)
		{
			return;
		}
		if (m_id != 0)
		{
			GLCall(glDeleteFramebuffers(1, &m_id));
			GLCall(glDeleteTextures(number, m_colorAttachment.data()));
			GLCall(glDeleteTextures(1, &m_depthAttachment));
			m_depthAttachment = 0;
			m_id = 0;
		}

		GLCall(glCreateFramebuffers(1, &m_id));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
		GLCall(glCreateTextures(GL_TEXTURE_2D, number, m_colorAttachment.data()));


		GLCall(glBindTexture(GL_TEXTURE_2D, m_colorAttachment[0]));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_size.x(), m_size.y(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		//GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_samples, GL_RGBA8, m_size.x(), m_size.y(), GL_FALSE));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment[0], 0));


		GLCall(glBindTexture(GL_TEXTURE_2D, m_colorAttachment[1]));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_size.x(), m_size.y(), 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		//GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_samples, GL_RGBA8, m_size.x(), m_size.y(), GL_FALSE));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_colorAttachment[1], 0));



		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_depthAttachment));
		GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_size.x(), m_size.y()));
		//GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_samples, GL_DEPTH24_STENCIL8, m_size.x(), m_size.y(), GL_FALSE));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0));
		

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			SE_CORE_ERROR("Something went wrong with the framebuffer {}", glCheckFramebufferStatus(GL_FRAMEBUFFER));
		}

		if (m_colorAttachment.size() > 1)
		{
			GLenum buffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			glDrawBuffers(m_colorAttachment.size(), buffers);
		}

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void Framebuffer::bind()
	{
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
		GLCall(glViewport(0, 0, m_size.x(), m_size.y()));
	}

	void Framebuffer::unbind()
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void Framebuffer::resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > 100000 || height > 100000)
		{
			SE_CORE_WARN("Trying to resize framebuffer ({0}) to width:{1} height:{2}", m_id, width, height);
			return;
		}
		m_size.x(width);
		m_size.y(height);

		invalidate();
	}

	void Framebuffer::clear(int index, int value)
	{
		GLCall(glClearTexImage(m_colorAttachment[index], 0, GL_RED_INTEGER, GL_INT, &value));
	}
}