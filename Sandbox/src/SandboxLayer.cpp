#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
	: Layer("SandboxLayer")
{
	float vertices[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 600.0f, 0.0f,
		600.0f, 0.0f, 0.0f
	};
	m_VBO = Cobweb::VertexBuffer::Create(vertices, sizeof(vertices));
	m_VBO->SetLayout({
		{ Cobweb::ShaderDataType::Float3, "Pos" }
		});

	uint32_t indices[] = {
		0, 1, 2
	};
	m_IBO = Cobweb::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_VAO = Cobweb::VertexArray::Create();
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);

	m_UBO = Cobweb::UniformBuffer::Create(4 * sizeof(float), 1);

	m_Shader = Cobweb::Shader::Create("Base", "assets/shaders/.bin/Base_vertex.spv", "assets/shaders/.bin/Base_pixel.spv");

	m_Camera.SetPosition({ -100.0f, -100.0f, 0.0f });
}

void SandboxLayer::OnUpdate()
{
	m_Camera.SetRotation(m_CameraRotation);
	Cobweb::Renderer::BeginScene(m_Camera);
	m_UBO->SetData(glm::value_ptr(m_Color), 4 * sizeof(float));
	Cobweb::Renderer::Submit(m_Shader, m_VAO);
	Cobweb::Renderer::EndScene();
}

void SandboxLayer::OnImGuiDraw()
{
	ImGui::Begin("Color");
	ImGui::ColorEdit4("Triangle", glm::value_ptr(m_Color));
	ImGui::SliderFloat("Rotation", &m_CameraRotation, -180.0f, 180.0f);
	ImGui::End();
}

void SandboxLayer::OnEvent(Cobweb::Event &e)
{
	Cobweb::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Cobweb::MouseButtonPressedEvent>(CW_BIND_FN(SandboxLayer::OnMouseButtonPressed));
}

bool SandboxLayer::OnMouseButtonPressed(Cobweb::MouseButtonPressedEvent &e)
{
	if (e.GetMouseButton() == CW_MOUSE_BUTTON_RIGHT)
		m_Color = m_Color == glm::vec4(0.0f) ? glm::vec4(1.0f) : glm::vec4(0.0f);
	return false;
}
