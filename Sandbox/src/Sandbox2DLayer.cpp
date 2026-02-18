#include "Sandbox2DLayer.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2DLayer")
{
	for (int i = 0; i < 2; i++)
	{
		m_Color[i] = glm::vec4(1.0f);
	}
}

void Sandbox2DLayer::OnUpdate(Cobweb::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	Cobweb::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Cobweb::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 100.0f, 100.0f }, m_Color[0]);
	Cobweb::Renderer2D::DrawQuad({ 200.0f, 200.0f }, { 200.0f, 200.0f }, m_Color[1]);

	Cobweb::Renderer2D::DrawQuad({ -200.0f, -200.0f }, { 100.0f, 100.0f }, m_Texture);

	Cobweb::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnImGuiDraw()
{
	const glm::vec3 &cameraPos = m_CameraController.GetCamera().GetPosition();

	ImGui::Begin("2D Scene");
	ImGui::Text("Camera Pos: (%.1f, %.1f)", cameraPos.x, cameraPos.y);
	ImGui::ColorEdit4("Color[0]", glm::value_ptr(m_Color[0]));
	ImGui::ColorEdit4("Color[1]", glm::value_ptr(m_Color[1]));
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Cobweb::Event &e)
{
	m_CameraController.OnEvent(e);
}
