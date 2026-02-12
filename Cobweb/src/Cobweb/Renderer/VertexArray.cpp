#include "cwpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cobweb
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
