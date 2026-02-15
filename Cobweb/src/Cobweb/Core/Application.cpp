#include "cwpch.h"
#include "Application.h"

#include "TimeStep.h"

#include "Cobweb/Renderer/Renderer.h"
#include "Cobweb/Renderer/Renderer2D.h"

// temporary
#include <GLFW/glfw3.h>

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

		m_Window = Window::Create();
		m_Window->SetEventCallback(CW_BIND_FN(Application::OnEvent));

		m_LastFrameTime = (float)glfwGetTime();

		Renderer::Init();
		Renderer2D::Init();

		m_Layers.PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer::ShutDown();
		Renderer2D::ShutDown();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;


			RenderCommand::SetClearColor({ 0.8f, 0.2f, 0.5f, 1.0f });
			RenderCommand::Clear();

			for (Layer *layer : m_Layers)
				layer->OnUpdate(timeStep);

			m_ImGuiLayer->Begin();
			for (Layer *layer : m_Layers)
				layer->OnImGuiDraw();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(CW_BIND_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(CW_BIND_FN(Application::OnWindowResized));

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

	bool Application::OnWindowResized(WindowResizedEvent &e)
	{
		Renderer::OnWindowResized(e);

		return false;
	}
}
