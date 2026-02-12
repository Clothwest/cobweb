#pragma once

#include "VertexArray.h"

#include "Cobweb/Core/Core.h"

#include <glm/glm.hpp>

namespace Cobweb
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL
		};

	public:
		static Scope<RendererAPI> Create();

	public:
		virtual ~RendererAPI() = default;

		virtual void Clear() const = 0;

		virtual void DrawIndexed(const Ref<VertexArray> &vao) const = 0;
		
		virtual void SetClearColor(const glm::vec4 &color) const = 0;

	protected:
		RendererAPI() = default;

	private:
		static API s_API;
	};
}
