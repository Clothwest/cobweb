#include "cwpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobweb
{
	Ref<Shader> Shader::Create(const std::string &name, const std::string &vertexPath, const std::string &pixelPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexPath, pixelPath);
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
