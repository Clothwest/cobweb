#include "Cobweb.h"

#include "imgui/imgui.h"

//// Include all GLM core / GLSL features
//#include <glm/glm.hpp> // vec2, vec3, mat4, radians
//
//// Include all GLM extensions
//#include <glm/ext.hpp> // perspective, translate, rotate
//
//glm::mat4 transform(glm::vec2 const &Orientation, glm::vec3 const &Translate, glm::vec3 const &Up)
//{
//	glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
//	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
//	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
//	glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
//	glm::mat4 Model = glm::mat4(1.0f);
//	return Proj * View * Model;
//}

class SandboxLayer : public Cobweb::Layer
{
public:
	SandboxLayer()
		: Cobweb::Layer("SandboxLayer")
	{
	}

	~SandboxLayer() = default;

	inline void OnAttach() override
	{
		CW_WARN("{} is pushed.", GetName());
	}
	
	inline void OnUpdate() override
	{
		//if (Cobweb::Input::IsMouseButtonPressed(CW_MOUSE_BUTTON_LEFT))
		//	CW_INFO("Clicked!");
	}

	inline void OnEvent(Cobweb::Event &e) override
	{
		//CW_INFO(e);
	}

	inline void OnImGuiRender() override
	{
		ImGui::Begin("Diagram");
		ImGui::End();
	}
};

class SandboxApp : public Cobweb::Application
{
public:
	SandboxApp()
	{
		PushLayer(new SandboxLayer());
	}

	~SandboxApp() = default;
};

Cobweb::Application *Cobweb::CreateApplication()
{
	return new SandboxApp();
}
