#include "cwpch.h"
#include "Application.h"

#include "Log.h"

// temporary

#include "Cobweb/Renderer/Shader.h"

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
		uint32_t vao;
		glCreateVertexArrays(1, &vao);

		uint32_t vbo;
		glCreateBuffers(1, &vbo);
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

		uint32_t ibo;
		glCreateBuffers(1, &ibo);
		uint32_t indices[] = {
			0, 1, 2
		};
		glNamedBufferData(ibo, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
		glVertexArrayAttribBinding(vao, 0, 0);

		glVertexArrayElementBuffer(vao, ibo);

		glCreateBuffers(1, &m_UBO);
		glNamedBufferStorage(m_UBO, 4 * sizeof(float), glm::value_ptr(m_Color), GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(m_UBO, 0, 4 * sizeof(float), glm::value_ptr(m_Color));
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_UBO);

		Ref<Shader> shader = Shader::Create("Base", "assets/shaders/.bin/Base_vertex.spv", "assets/shaders/.bin/Base_pixel.spv");

		while (m_Running)
		{
			glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glNamedBufferSubData(m_UBO, 0, 4 * sizeof(float), glm::value_ptr(m_Color));
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
		//m_Running = false;
		m_Color = m_Color == glm::vec4(0.0f) ? glm::vec4(1.0f) : glm::vec4(0.0f);
		return true;
	}
}
