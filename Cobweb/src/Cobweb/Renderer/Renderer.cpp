#include "cwpch.h"
#include "Renderer.h"

namespace Cobweb
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray> &vao)
	{
		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}
}
