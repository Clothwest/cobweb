#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
	: Layer("SandboxLayer")
{
	float pos[] = {
		-200.0f, -200.0f, 0.0f,
		 200.0f, -200.0f, 0.0f,
		 200.0f,  200.0f, 0.0f,
		-200.0f,  200.0f, 0.0f
	};
	float texCoord[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	Cobweb::Ref<Cobweb::VertexBuffer> posVBO = Cobweb::VertexBuffer::Create(pos, sizeof(pos));
	posVBO->SetLayout({
		{ Cobweb::ShaderDataType::Float3, "Pos" },
		});
	Cobweb::Ref<Cobweb::VertexBuffer> texCoordVBO = Cobweb::VertexBuffer::Create(texCoord, sizeof(texCoord));
	texCoordVBO->SetLayout({
		{ Cobweb::ShaderDataType::Float2, "TexCoord" }
		});

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	Cobweb::Ref<Cobweb::IndexBuffer> ibo = Cobweb::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_VAO = Cobweb::VertexArray::Create();
	m_VAO->AddVertexBuffer(posVBO);
	m_VAO->AddVertexBuffer(texCoordVBO);
	m_VAO->SetIndexBuffer(ibo);

	m_ShaderLibrary.Add(Cobweb::Shader::Create("Base", "assets/shaders/.bin/Base_vert.spv", "assets/shaders/.bin/Base_frag.spv"));

	m_Texture = Cobweb::Texture2D::Create("assets/textures/preview.jpg");
}

void SandboxLayer::OnUpdate(Cobweb::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	Cobweb::Ref<Cobweb::Shader> shader = m_ShaderLibrary.Get("Base");

	Cobweb::Renderer::BeginScene(m_CameraController.GetCamera());
	m_Texture->Bind(10);
	Cobweb::Renderer::Submit(shader, m_VAO);
	Cobweb::Renderer::EndScene();
}

void SandboxLayer::OnImGuiDraw()
{
	ImGui::Begin("Data");

	const glm::vec3 &cameraPos = m_CameraController.GetCamera().GetPosition();
	ImGui::Text("Camera Pos: (%.1f, %.1f)", cameraPos.x, cameraPos.y);

	ImGui::End();
}

void SandboxLayer::OnEvent(Cobweb::Event &e)
{
	m_CameraController.OnEvent(e);

	Cobweb::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Cobweb::MouseButtonPressedEvent>(CW_BIND_FN(SandboxLayer::OnMouseButtonPressed));
}

bool SandboxLayer::OnMouseButtonPressed(Cobweb::MouseButtonPressedEvent &e)
{
	return false;
}
