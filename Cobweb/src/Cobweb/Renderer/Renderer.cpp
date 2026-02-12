#include "cwpch.h"
#include "Renderer.h"

namespace Cobweb
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = nullptr;

	void Renderer::Init()
	{
		RenderCommand::Init();

		s_SceneData = CreateScope<Renderer::SceneData>();
	}

	void Renderer::ShutDown()
	{
		s_SceneData = nullptr;
	}

	void Renderer::BeginScene(const OrthographicCamera &camera)
	{
		s_SceneData->CameraUBO->SetData(glm::value_ptr(camera.GetViewProjectionMatrix()), sizeof(glm::mat4));
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vao, const glm::mat4 &transform)
	{
		shader->Bind();
		vao->Bind();
		s_SceneData->TransformUBO->SetData(glm::value_ptr(transform), sizeof(glm::mat4));
		RenderCommand::DrawIndexed(vao);
	}
}
