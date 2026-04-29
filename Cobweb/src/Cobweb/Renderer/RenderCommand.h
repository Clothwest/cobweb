#pragma once

#include "RendererAPI.h"

namespace Cobweb
{
	class RenderCommand
	{
	public:
		~RenderCommand() = default;

		static void Init();

		static void DrawIndexed(const Ref<VertexArray> &vao);
		static void DrawIndexed(const Ref<VertexArray> &vao, uint32_t indexCount);
		static void Clear();
		static void SetClearColor(const glm::vec4 &color);
		static void SetViewport(int width, int height);

	private:
		RenderCommand() = default;

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}
