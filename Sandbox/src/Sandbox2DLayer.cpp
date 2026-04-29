#include "Sandbox2DLayer.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2DLayer")
{
	for (int i = 0; i < 2; i++)
	{
		m_Color[i] = glm::vec4(1.0f);
	}

	m_Particle.Position = { 0.0f, 0.0f };
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 300.0f, 300.0f };
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 50.0f, m_Particle.SizeVariation = 0.0f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 2.0f;

	m_SubTexture[0] = Cobweb::CreateRef<Cobweb::SubTexture2D>(m_Sheet, glm::vec2{ 0.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
	m_SubTexture[1] = Cobweb::CreateRef<Cobweb::SubTexture2D>(m_Sheet, glm::vec2{ 32.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
	m_SubTexture[2] = Cobweb::CreateRef<Cobweb::SubTexture2D>(m_Sheet, glm::vec2{ 64.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
	m_SubTexture[3] = Cobweb::CreateRef<Cobweb::SubTexture2D>(m_Sheet, glm::vec2{ 96.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
}

void Sandbox2DLayer::OnUpdate(Cobweb::TimeStep ts)
{
	Cobweb::Renderer2D::ResetStatistics();

	m_CameraController.OnUpdate(ts);
	m_ParticleSystem.OnUpdate(ts);

	Cobweb::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Cobweb::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 100.0f, 100.0f }, m_Color[0]);
	Cobweb::Renderer2D::DrawQuad({ 200.0f, 200.0f }, { 200.0f, 200.0f }, m_Color[1]);

	Cobweb::Renderer2D::DrawQuad({ -200.0f, -200.0f }, { 100.0f, 100.0f }, m_Texture, 2.0f);

	Cobweb::Renderer2D::DrawRotatedQuad({ 0.0f, -100.0f }, { 200.0f, 200.0f }, glm::pi<float>() / 6.0f, m_Texture);

	static float seconds = 0;
	static uint32_t index = 0;
	if (seconds * 4.0f >= 1.0f)
	{
		index = (index + 1) % 4;
		seconds = 0.0f;
	}
	Cobweb::Renderer2D::DrawQuad({ 200.0f, -200.0f }, { 100.0f, 100.0f }, m_SubTexture[index]);
	seconds += ts.GetSeconds();

	Cobweb::Renderer2D::EndScene();

	if (Cobweb::Input::IsMouseButtonPressed(CW_MOUSE_BUTTON_LEFT))
	{
		const auto &[x, y] = Cobweb::Input::GetMousePos();
		const auto &[width, height] = Cobweb::Application::Get().GetWindow().GetDisplaySize();

		const glm::vec2 &camPosition = m_CameraController.GetCamera().GetPosition();
		glm::vec4 camBound = m_CameraController.GetBound();
		float camZoomLevel = m_CameraController.GetZoomLevel();

		camBound /= camZoomLevel;

		m_Particle.Position = glm::vec2{ (x - (float)width / 2.0f) / ((float)width / 2.0f) * camBound.y, (y - (float)height / 2.0f) / ((float)height / 2.0f) * camBound.w } + camPosition;

		for (int i = 0; i < 4; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
}

void Sandbox2DLayer::OnImGuiDraw()
{
	const glm::vec3 &cameraPos = m_CameraController.GetCamera().GetPosition();
	float cameraRot = m_CameraController.GetCamera().GetRotation();

	const auto &[x, y] = Cobweb::Input::GetMousePos();
	const auto &[width, height] = Cobweb::Application::Get().GetWindow().GetDisplaySize();

	ImGui::Begin("2D Scene");
	ImGui::Text("Camera Pos: (%.1f, %.1f)", cameraPos.x, cameraPos.y);
	ImGui::Text("Camera Rot: %.1f", cameraRot);
	ImGui::ColorEdit4("Color[0]", glm::value_ptr(m_Color[0]));
	ImGui::ColorEdit4("Color[1]", glm::value_ptr(m_Color[1]));

	ImGui::Text("MousePos: (%.1f, %.1f)", x, y);
	ImGui::Text("DisplaySize: (%.1f, %.1f)", (float)width, (float)height);
	ImGui::Text("ParticlePos: (%.1f, %.1f)", x - (float)width / 2.0f, y - (float)height / 2.0f);
	ImGui::End();

	Cobweb::Renderer2D::Statistics stats = Cobweb::Renderer2D::GetStatistics();

	ImGui::Begin("Statistics");
	ImGui::Text("DrawCall: %d", stats.DrawCallCount);
	ImGui::Text("Quad: %d", stats.QuadCount);
	ImGui::Text("Vertex: %d", stats.VertexCount);
	ImGui::Text("Index: %d", stats.IndexCount);
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Cobweb::Event &e)
{
	m_CameraController.OnEvent(e);
}
