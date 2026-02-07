#include "cwpch.h"
#include "Application.h"

namespace Cobweb
{
	Application::Application()
	{
		m_Window->SetEventCallback(CW_BIND_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event &e)
	{
		CW_CORE_TRACE(e);

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(CW_BIND_FN(Application::OnWindowClosed));
	}

	bool Application::OnWindowClosed(WindowClosedEvent &e)
	{
		m_Running = false;
		return true;
	}
}
