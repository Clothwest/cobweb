#include "cwpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobweb
{
	Ref<Shader> Shader::Create(const std::string &name, const std::string &vertexPath, const std::string &pixelPath)
	{
		return CreateRef<OpenGLShader>(name, vertexPath, pixelPath);
	}
}
