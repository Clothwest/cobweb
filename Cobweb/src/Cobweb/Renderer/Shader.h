#pragma once

#include "Cobweb/Core/Core.h"

#include <glm/glm.hpp>

#include <string>
#include <type_traits>

namespace Cobweb
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string &name, const std::string &vertexPath, const std::string &pixelPath);

	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string &GetName() const = 0;

	protected:
		Shader() = default;
	};
}
