#include "cwpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cobweb
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}
