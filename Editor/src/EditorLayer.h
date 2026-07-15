#pragma once

#include <Cobweb.h>

namespace Cobweb
{
	class EditorLayer: public Layer
	{
	public:
		EditorLayer();
		~EditorLayer() = default;

		void OnUpdate(TimeStep ts) override;
		void OnImGuiDraw() override;
		void OnEvent(Event &e) override;

	private:
		OrthographicCameraController m_CameraController = { -640.0f, 640.0f, -360.0f, 360.0f, true };

		Ref<Texture2D> m_Texture = Texture2D::Create("assets/textures/preview.jpg");
		Ref<Texture2D> m_Sheet = Texture2D::Create("assets/textures/W.png");
		Ref<SubTexture2D> m_SubTexture[4];

		glm::vec4 m_Color[2];

		Ref<FrameBuffer> m_FrameBuffer = FrameBuffer::Create({ 1280, 720 });
		glm::u32vec2 m_ViewportSize = { 1280, 720 };

		bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}
