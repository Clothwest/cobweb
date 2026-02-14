#pragma once

#include <Cobweb.h>

class SandboxLayer : public Cobweb::Layer
{
public:
	SandboxLayer();
	~SandboxLayer() = default;

	void OnUpdate(Cobweb::TimeStep ts) override;
	void OnImGuiDraw() override;
	void OnEvent(Cobweb::Event &e) override;

private:
	bool OnMouseButtonPressed(Cobweb::MouseButtonPressedEvent &e);

private:
	Cobweb::Ref<Cobweb::VertexArray> m_VAO;

	Cobweb::ShaderLibrary m_ShaderLibrary;

	Cobweb::Ref<Cobweb::Texture2D> m_Texture;

	Cobweb::OrthographicCameraController m_CameraController = Cobweb::OrthographicCameraController(-640.0f, 640.0f, -360.0f, 360.0f, true);
};
