#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

namespace Cobweb
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);

	private:
		bool OnWindowClosed(WindowClosedEvent &e);

	private:
		bool m_Running = true;

		Scope<Window> m_Window = Window::Create();

		LayerStack m_Layers;
	};

	// To bo defined in CLIENT
	Application *CreateApplication();
}

