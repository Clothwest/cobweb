#include "cwpch.h"
#include "Renderer2D.h"

namespace Cobweb
{
	Scope<Renderer2D::SceneData> Renderer2D::s_SceneData = nullptr;

	void Renderer2D::Init()
	{
		s_SceneData = CreateScope<SceneData>();

		float vertices[] = {
			0.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f,  0.0f, 0.0f,
			0.0f,  0.0f, 0.0f
		};
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" }
			});

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		s_SceneData->VertexArray->AddVertexBuffer(vertexBuffer);
		s_SceneData->VertexArray->SetIndexBuffer(indexBuffer);
	}

	void Renderer2D::ShutDown()
	{
		s_SceneData = nullptr;
	}

	void Renderer2D::BeginScene(const OrthographicCamera &camera)
	{
		s_SceneData->Shader->Bind();
		s_SceneData->VertexArray->Bind();

		s_SceneData->UniformBuffer->SetData(glm::value_ptr(camera.GetViewProjectionMatrix()), sizeof(glm::mat4), 0);
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color)
	{
		DrawQuad(glm::vec3(pos, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_SceneData->UniformBuffer->SetData(glm::value_ptr(transform), sizeof(glm::mat4), sizeof(glm::mat4));

		s_SceneData->UniformBuffer->SetData(glm::value_ptr(color), sizeof(glm::vec4), sizeof(glm::mat4) + sizeof(glm::mat4));

		RenderCommand::DrawIndexed(s_SceneData->VertexArray);
	}
}
