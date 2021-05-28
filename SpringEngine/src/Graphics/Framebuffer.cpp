#include <SpringEngine/Graphics/Framebuffer.hpp>

namespace SE
{
	GLenum getTextureType(int samples)
	{
		if (samples > 1)
		{
			return GL_TEXTURE_2D_MULTISAMPLE;
		}
		else
		{
			return GL_TEXTURE_2D;
		}
	}

	GLenum getFormat(FramebufferAttachmentType type, int channels)
	{
		if (type == FramebufferAttachmentType::COLOR)
		{
			if (channels == 4)
			{
				return GL_RGBA;
			}
			else
			{
				return GL_RGB;
			}
		}
		else
		{
			return GL_RED_INTEGER;
		}
	}

	GLenum getInternalFormat(FramebufferAttachmentType type)
	{
		if (type == FramebufferAttachmentType::COLOR)
		{
			return GL_RGBA16F;
		}
		else if (type == FramebufferAttachmentType::INTEGER)
		{
			return GL_R32I;
		}
	}

	Framebuffer::Framebuffer(Vector2<unsigned int> size, std::vector<FramebufferAttachment> attachments) : m_id(0), m_size(size), m_samples(16), m_attachmentsSpecification(attachments)
	{
		//m_attachmentsSpecification.push_back({ FramebufferAttachmentType::COLOR, 4 });
		//m_attachmentsSpecification.push_back({ FramebufferAttachmentType::COLOR, 3 });
		//m_attachmentsSpecification.push_back({ FramebufferAttachmentType::COLOR, 3 });
		//m_attachmentsSpecification.push_back({ FramebufferAttachmentType::COLOR, 4 });
		//m_attachmentsSpecification.push_back({ FramebufferAttachmentType::INTEGER, 1 });
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
		m_colorAttachment.resize(m_attachmentsSpecification.size());
		if (m_size.x() == 0 || m_size.y() == 0)
		{
			return;
		}
		if (m_id != 0)
		{
			GLCall(glDeleteFramebuffers(1, &m_id));
			GLCall(glDeleteTextures(m_colorAttachment.size(), m_colorAttachment.data()));
			GLCall(glDeleteTextures(1, &m_depthAttachment));
			m_depthAttachment = 0;
			m_id = 0;
		}

		GLCall(glCreateFramebuffers(1, &m_id));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
		GLCall(glCreateTextures(GL_TEXTURE_2D, m_colorAttachment.size(), m_colorAttachment.data()));

		unsigned int i = 0;
		for (auto spec : m_attachmentsSpecification)
		{
			GLCall(glBindTexture(getTextureType(spec.samples), m_colorAttachment[i]));

			if (spec.samples == 1)
			{
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(spec.type), m_size.x(), m_size.y(), 0,
						getFormat(spec.type, spec.channels), spec.canGoNegative ? GL_FLOAT : GL_UNSIGNED_BYTE, nullptr));

				if (spec.type == FramebufferAttachmentType::INTEGER)
				{
					GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
					GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
				}
				else
				{
					GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
					GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				}
			}
			else
			{
				GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, spec.samples, getInternalFormat(spec.type), m_size.x(), m_size.y(), GL_FALSE));
			}

			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, getTextureType(spec.samples), m_colorAttachment[i], 0));
			i++;
		}

		//GLCall(glCreateTextures(getTextureType(m_attachmentsSpecification[0].samples), 1, &m_depthAttachment));
		//GLCall(glBindTexture(getTextureType(m_attachmentsSpecification[0].samples), m_depthAttachment));
		//if (m_attachmentsSpecification[0].samples == 1)
		//{
		//	GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_size.x(), m_size.y()));
		//}
		//else
		//{
		//	GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_attachmentsSpecification[0].samples, GL_DEPTH24_STENCIL8, m_size.x(), m_size.y(), GL_FALSE));
		//}
		//GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, getTextureType(m_attachmentsSpecification[0].samples), m_depthAttachment, 0));
		
		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_depthAttachment));
		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT, m_size.x(), m_size.y()));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_size.x(), m_size.y(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
		//GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			SE_CORE_ERROR("Something went wrong with the framebuffer {}", glCheckFramebufferStatus(GL_FRAMEBUFFER));
		}

		if (m_colorAttachment.size() > 1)
		{
			GLenum buffers[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
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

	void Framebuffer::bindRead()
	{
		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id));
	}

	void Framebuffer::bindWrite()
	{
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id));
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