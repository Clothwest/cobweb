#pragma once

#include "Base.h"
#include "Window.h"
#include "LayerStack.h"
#include "Cobweb/ImGui/ImGuiLayer.h"

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
		inline ImGuiLayer *GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClosed(WindowClosedEvent &e);
		bool OnWindowResized(WindowResizedEvent &e);

	private:
		bool m_Running = true;
		float m_LastFrameTime;

		Window *m_Window;

		LayerStack m_Layers;
		ImGuiLayer *m_ImGuiLayer = new ImGuiLayer();

	private:
		static Application *s_Instance;
	};

	// To bo defined in CLIENT
	Application *CreateApplication();
}

