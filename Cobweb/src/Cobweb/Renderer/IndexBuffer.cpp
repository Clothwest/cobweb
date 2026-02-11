#include "cwpch.h"
#include "IndexBuffer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobweb
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
	{
		return CreateRef<OpenGLIndexBuffer>(indices, count);
	}
}
