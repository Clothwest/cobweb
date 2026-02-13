#pragma once

#include "Cobweb/Renderer/Shader.h"

#include <vector>
#include <unordered_map>

namespace Cobweb
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string &name, const std::string &vertPath, const std::string &fragPath);
		~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

		inline const std::string &GetName() const override { return m_Name; }

	private:
		std::vector<char> ReadFile(const std::string &filePath);

		uint32_t CreateShader(uint32_t type, const std::string &filePath);
		uint32_t CreateProgram(uint32_t vertShader, uint32_t fragShader);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
