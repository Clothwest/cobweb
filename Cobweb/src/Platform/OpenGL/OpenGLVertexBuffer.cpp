#include "cwpch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Cobweb
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
