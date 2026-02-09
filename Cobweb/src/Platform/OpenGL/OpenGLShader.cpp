#include "cwpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Cobweb
{
	OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexPath, const std::string &pixelPath)
		: m_Name(name)
	{
		uint32_t vertexShader = CreateShader(GL_VERTEX_SHADER, vertexPath);
		uint32_t pixelShader = CreateShader(GL_FRAGMENT_SHADER, pixelPath);
		m_RendererID = CreateProgram(vertexShader, pixelShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	std::vector<char> OpenGLShader::ReadFile(const std::string &filePath)
	{
		std::vector<char> result;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (!in)
			CW_CORE_ERROR("Could not open file \"{}\"", filePath);
		else
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(result.data(), result.size());
			in.close();
		}
		return result;
	}

	uint32_t OpenGLShader::CreateShader(uint32_t type, const std::string &filePath)
	{
		const char *entryPoint = nullptr;
		switch (type)
		{
			case GL_VERTEX_SHADER:
				entryPoint = "VSMain";
				break;
			case GL_FRAGMENT_SHADER:
				entryPoint = "PSMain";
				break;
		}
		CW_CORE_ASSERT(entryPoint, "Unknown shader type!");

		std::vector<char> spirvCode = ReadFile(filePath);
		CW_CORE_ASSERT(!spirvCode.empty(), "Code is empty!");

		uint32_t shader = glCreateShader(type);
		glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, spirvCode.data(), (int)(spirvCode.size()));
		glSpecializeShader(shader, entryPoint, 0, nullptr, nullptr);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			std::vector<char> infoLog(logSize);

			glGetShaderInfoLog(shader, logSize, &logSize, &infoLog[0]);
			const char *shaderName;
			if (type == GL_VERTEX_SHADER)
				shaderName = "Vertex";
			else if (type == GL_FRAGMENT_SHADER)
				shaderName = "Pixel/Fragment";
			else
				shaderName = "Other";
			CW_CORE_ERROR("{0}: {1}", shaderName, infoLog.data());
			CW_CORE_ASSERT(false, "Failed to compile shader!");
		}

		return shader;
	}

	uint32_t OpenGLShader::CreateProgram(uint32_t vertexShader, uint32_t pixelShader)
	{
		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, pixelShader);
		glLinkProgram(program);

		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			int logSize;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
			std::vector<char> infoLog(logSize);

			glGetProgramInfoLog(program, logSize, &logSize, &infoLog[0]);
			CW_CORE_ERROR("{0}: {1}", "Program linking", infoLog.data());
			CW_CORE_ASSERT(false, "Failed to link program!");
		}

		glDeleteShader(vertexShader);
		glDeleteShader(pixelShader);

		return program;
	}
}
