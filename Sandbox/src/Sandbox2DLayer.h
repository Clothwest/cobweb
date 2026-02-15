#pragma once

#include <Cobweb.h>

class Sandbox2DLayer : public Cobweb::Layer
{
public:
	Sandbox2DLayer();
	~Sandbox2DLayer() = default;

	void OnUpdate(Cobweb::TimeStep ts) override;
	void OnImGuiDraw() override;
	void OnEvent(Cobweb::Event &e) override;

private:
	Cobweb::OrthographicCameraController m_CameraController = { -640.0f, 640.0f, -360.0f, 360.0f, true };

	glm::vec4 m_Color[2];
};
