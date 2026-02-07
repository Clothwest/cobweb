#include "Cobweb.h"

#include "imgui/imgui.h"

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
