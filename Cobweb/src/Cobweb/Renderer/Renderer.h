#pragma once

#include "RenderCommand.h"

#include "Cobweb/Core/Core.h"

namespace Cobweb
{
	class Renderer
	{
	public:
		~Renderer() = default;

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray> &vao);

	private:
		Renderer() = default;
	};
}
