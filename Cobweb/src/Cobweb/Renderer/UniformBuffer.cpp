#include "cwpch.h"
#include "UniformBuffer.h"

#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Cobweb
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t bindingIndex)
	{
		return CreateRef<OpenGLUniformBuffer>(size, bindingIndex);
	}
}
