#pragma once

#include "ParticleSystem.h"

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

	Cobweb::Ref<Cobweb::Texture2D> m_Texture = Cobweb::Texture2D::Create("assets/textures/preview.jpg");
	Cobweb::Ref<Cobweb::Texture2D> m_Sheet = Cobweb::Texture2D::Create("assets/textures/W.png");
	Cobweb::Ref<Cobweb::SubTexture2D> m_SubTexture[4];

	glm::vec4 m_Color[2];

	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;
};
