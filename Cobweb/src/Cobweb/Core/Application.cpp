#include "cwpch.h"
#include "Application.h"

#include "Log.h"

// temporary
#include <glad/glad.h>

namespace Cobweb
{
	Application *Application::s_Instance = nullptr;

	Application &Application::Get()
	{
		CW_CORE_ASSERT(s_Instance, "Application does not exist!");
		return *s_Instance;
	}

	Application::Application()
	{
		CW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window->SetEventCallback(CW_BIND_FN(Application::OnEvent));

		m_Layers.PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer *layer : m_Layers)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer *layer : m_Layers)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

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
			if (e.IsHandled())
				break;
			(*it)->OnEvent(e);
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
