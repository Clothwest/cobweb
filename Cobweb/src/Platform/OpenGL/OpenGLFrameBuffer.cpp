#include "cwpch.h"
#include "OpenGLFrameBuffer.h"

#include "Cobweb/Core/Log.h"

#include <glad/glad.h>

namespace Cobweb
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification &spec)
		: m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteRenderbuffers(1, &m_DepthAttachment);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

    void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
    {
		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}

	const FrameBufferSpecification &OpenGLFrameBuffer::GetSpecification() const
	{
		return m_Specification;
	}

	uint32_t OpenGLFrameBuffer::GetTextureID() const
	{
		return m_ColorAttachment;
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_Specification.Width == 0 || m_Specification.Height == 0)
		{
			return;
		}

		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteRenderbuffers(1, &m_DepthAttachment);
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Specification.Width, m_Specification.Height);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glCreateRenderbuffers(1, &m_DepthAttachment);
		glNamedRenderbufferStorage(m_DepthAttachment, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);

		glCreateFramebuffers(1, &m_RendererID);
		glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_ColorAttachment, 0);
		glNamedFramebufferRenderbuffer(m_RendererID, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment);

		CW_CORE_ASSERT(glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete!");
	}
}
