#include "cwpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobweb
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
