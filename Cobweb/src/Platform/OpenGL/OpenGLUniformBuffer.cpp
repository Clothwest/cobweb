#include "cwpch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace Cobweb
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t bindingIndex)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferStorage(m_RendererID, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset) const
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}
