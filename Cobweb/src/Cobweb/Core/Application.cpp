#include "cwpch.h"
#include "Application.h"

#include "Log.h"

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
			for (Layer *layer : m_Layers)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event &e)
	{
		//CW_CORE_TRACE(e);

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(CW_BIND_FN(Application::OnWindowClosed));

		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++)
		{
			(*it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer *layer)
	{
		m_Layers.PushLayer(layer);
	}

	void Application::PushOverlay(Layer *overlay)
	{
		m_Layers.PushOverlay(overlay);
	}

	bool Application::OnWindowClosed(WindowClosedEvent &e)
	{
		m_Running = false;
		return true;
	}
}
