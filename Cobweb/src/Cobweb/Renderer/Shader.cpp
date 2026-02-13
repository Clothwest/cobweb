#include "cwpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobweb
{
	Ref<Shader> Shader::Create(const std::string &name, const std::string &vertPath, const std::string &fragPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertPath, fragPath);
		}

		CW_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader> &shader)
	{
		CW_CORE_ASSERT(!Has(shader), "Shader \"{}\" already exists!", shader->GetName());
		m_Shaders[shader->GetName()] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &vertPath, const std::string &fragPath)
	{
		CW_CORE_ASSERT(!Has(name), "Shader \"{}\" already exists!", name);
		return m_Shaders[name] = Shader::Create(name, vertPath, fragPath);
	}

	Ref<Shader> ShaderLibrary::Get(const std::string &name)
	{
		CW_CORE_ASSERT(Has(name), "Shader \"{}\" does not exist!", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Has(const std::string &name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	bool ShaderLibrary::Has(const Ref<Shader> &shader)
	{
		return Has(shader->GetName());
	}
}
