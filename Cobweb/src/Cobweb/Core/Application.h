#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Cobweb/ImGui/ImGuiLayer.h"

// temporary
#include <glm/glm.hpp>

namespace Cobweb
{
	class Application
	{
	public:
		static Application &Get();

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);

		inline Window &GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowClosedEvent &e);

	private:
		bool m_Running = true;

		Scope<Window> m_Window = Window::Create();

		LayerStack m_Layers;
		ImGuiLayer *m_ImGuiLayer = new ImGuiLayer();

		glm::vec4 m_Color = glm::vec4(1.0f);
		uint32_t m_UBO;

	private:
		static Application *s_Instance;
	};

	// To bo defined in CLIENT
	Application *CreateApplication();
}

