#pragma once

#include "Cobweb/Renderer/RendererAPI.h"

namespace Cobweb
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI() = default;
		~OpenGLRendererAPI() = default;

		void Init() const override;

		void DrawIndexed(const Ref<VertexArray> &vao) const override;
		void DrawIndexed(const Ref<VertexArray> &vao, uint32_t indexCount) const override;
		void Clear() const override;
		void SetClearColor(const glm::vec4 &color) const override;
		void SetViewport(int width, int height) const override;
	};
}
