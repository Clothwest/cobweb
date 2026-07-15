#include "EditorLayer.h"

namespace Cobweb
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
		for (int i = 0; i < 2; i++)
		{
			m_Color[i] = glm::vec4(1.0f);
		}

		m_SubTexture[0] = CreateRef<SubTexture2D>(m_Sheet, glm::vec2{ 0.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
		m_SubTexture[1] = CreateRef<SubTexture2D>(m_Sheet, glm::vec2{ 32.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
		m_SubTexture[2] = CreateRef<SubTexture2D>(m_Sheet, glm::vec2{ 64.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
		m_SubTexture[3] = CreateRef<SubTexture2D>(m_Sheet, glm::vec2{ 96.0f, 128.0f }, glm::vec2{ 32.0f, 32.0f });
	}

	void EditorLayer::OnUpdate(TimeStep ts)
	{
		const FrameBufferSpecification &specification = m_FrameBuffer->GetSpecification();
		if (m_ViewportSize != glm::u32vec2(specification.Width, specification.Height))
		{
			m_FrameBuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
			m_CameraController.Resize(m_ViewportSize);
		}

		m_FrameBuffer->Bind();
		RenderCommand::SetViewport(m_ViewportSize.x, m_ViewportSize.y);
		RenderCommand::Clear();

		Renderer2D::ResetStatistics();

		if (m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		Renderer2D::BeginScene(m_CameraController.GetCamera());
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 100.0f, 100.0f }, m_Color[0]);
		Renderer2D::DrawQuad({ 200.0f, 200.0f }, { 200.0f, 200.0f }, m_Color[1]);

		Renderer2D::DrawQuad({ -200.0f, -200.0f }, { 100.0f, 100.0f }, m_Texture, 2.0f);

		Renderer2D::DrawRotatedQuad({ 0.0f, -100.0f }, { 200.0f, 200.0f }, glm::pi<float>() / 6.0f, m_Texture);

		static float seconds = 0;
		static uint32_t index = 0;
		if (seconds * 4.0f >= 1.0f)
		{
			index = (index + 1) % 4;
			seconds = 0.0f;
		}
		Renderer2D::DrawQuad({ 200.0f, -200.0f }, { 100.0f, 100.0f }, m_SubTexture[index]);
		seconds += ts.GetSeconds();

		Renderer2D::EndScene();

		m_FrameBuffer->UnBind();
	}

	void EditorLayer::OnImGuiDraw()
	{
		ImGui::DockSpaceOverViewport();

		ImGui::Begin("Panel");

		ImGui::ColorEdit4("Color0", glm::value_ptr(m_Color[0]));
		ImGui::ColorEdit4("Color1", glm::value_ptr(m_Color[1]));
		int testInput = 0;
		ImGui::InputInt("TestInput", &testInput);

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("framebuffer");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 size = ImGui::GetContentRegionAvail();
		m_ViewportSize = { (uint32_t)size.x, (uint32_t)size.y };

		ImGui::Image(m_FrameBuffer->GetTextureID(), { (float)m_ViewportSize.x, (float)m_ViewportSize.y }, { 0.0f, 1.0f }, { 1.0f, 0.0f });

		ImGui::End();
		ImGui::PopStyleVar(1);

		Renderer2D::Statistics stats = Renderer2D::GetStatistics();

		ImGui::Begin("Statistics");
		ImGui::Text("DrawCall: %d", stats.DrawCallCount);
		ImGui::Text("Quad: %d", stats.QuadCount);
		ImGui::Text("Vertex: %d", stats.VertexCount);
		ImGui::Text("Index: %d", stats.IndexCount);
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event &e)
	{
		m_CameraController.OnEvent(e);
	}
}
