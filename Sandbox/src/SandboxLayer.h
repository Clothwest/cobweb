#pragma once

#include <Cobweb.h>

class SandboxLayer : public Cobweb::Layer
{
public:
	SandboxLayer();
	~SandboxLayer() = default;

	void OnUpdate() override;
	void OnImGuiDraw() override;
	void OnEvent(Cobweb::Event &e) override;

private:
	bool OnMouseButtonPressed(Cobweb::MouseButtonPressedEvent &e);

private:
	Cobweb::Ref<Cobweb::VertexArray> m_VAO;
	Cobweb::Ref<Cobweb::VertexBuffer> m_VBO;
	Cobweb::Ref<Cobweb::IndexBuffer> m_IBO;

	Cobweb::Ref<Cobweb::UniformBuffer> m_UBO;

	Cobweb::Ref<Cobweb::Shader> m_Shader;

	Cobweb::OrthographicCamera m_Camera = Cobweb::OrthographicCamera(-1280.0f, 1280.0f, -720.0f, 720.0f);

	glm::vec4 m_Color = glm::vec4(1.0f);
	float m_CameraRotation = 0.0f;
};
