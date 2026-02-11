#include "cwpch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Cobweb
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
