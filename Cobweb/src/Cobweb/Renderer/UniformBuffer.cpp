#include "cwpch.h"
#include "UniformBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Cobweb
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t bindingIndex)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLUniformBuffer>(size, bindingIndex);
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
