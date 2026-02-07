#pragma once

#include "Core.h"
#include "Window.h"

namespace Cobweb
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

	private:
		bool OnWindowClosed(WindowClosedEvent &e);

	private:
		bool m_Running = true;

		Scope<Window> m_Window = Window::Create();
	};

	// To bo defined in CLIENT
	Application *CreateApplication();
}

