#include "cwpch.h"
#include "RenderCommand.h"

namespace Cobweb
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray> &vao)
	{
		s_RendererAPI->DrawIndexed(vao);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray> &vao, uint32_t indexCount)
	{
		s_RendererAPI->DrawIndexed(vao, indexCount);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::SetClearColor(const glm::vec4 &color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::SetViewport(int width, int height)
	{
		s_RendererAPI->SetViewport(width, height);
	}
}
