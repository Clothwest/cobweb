#pragma once

#include "RendererAPI.h"

namespace Cobweb
{
	class RenderCommand
	{
	public:
		~RenderCommand() = default;

		static void Clear();

		static void DrawIndexed(const Ref<VertexArray> &vao);

		static void SetClearColor(const glm::vec4 &color);

	private:
		RenderCommand() = default;

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}
