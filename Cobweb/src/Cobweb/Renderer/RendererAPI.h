#pragma once

#include "VertexArray.h"

#include "Cobweb/Core/Base.h"

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

		static inline API GetAPI() { return s_API; }

	public:
		virtual ~RendererAPI() = default;

		virtual void Init() const = 0;

		virtual void DrawIndexed(const Ref<VertexArray> &vao) const = 0;
		virtual void DrawIndexed(const Ref<VertexArray> &vao, uint32_t indexCount) const = 0;
		virtual void Clear() const = 0;
		virtual void SetClearColor(const glm::vec4 &color) const = 0;
		virtual void SetViewport(int width, int height) const = 0;

	protected:
		RendererAPI() = default;

	private:
		static API s_API;
	};
}
