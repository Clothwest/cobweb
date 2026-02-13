#pragma once

#include "Cobweb/Core/Core.h"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Cobweb
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string &name, const std::string &vertPath, const std::string &fragPath);

	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string &GetName() const = 0;

	protected:
		Shader() = default;
	};

	class ShaderLibrary
	{
	public:
		ShaderLibrary() = default;
		~ShaderLibrary() = default;

		void Add(const Ref<Shader> &shader);

		Ref<Shader> Load(const std::string &name, const std::string &vertexPath, const std::string &pixelPath);

		Ref<Shader> Get(const std::string &name);

	private:
		bool Has(const std::string &name);
		bool Has(const Ref<Shader> &shader);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}
