#include "cwpch.h"
#include "FrameBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

#include "Cobweb/Core/Log.h"

namespace Cobweb
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification &spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
