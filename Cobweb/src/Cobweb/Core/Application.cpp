#include "cwpch.h"
#include "Application.h"

#include "Log.h"

// temporary

#include "Cobweb/Renderer/Shader.h"
#include "Cobweb/Renderer/IndexBuffer.h"
#include "Cobweb/Renderer/VertexBuffer.h"
#include "Cobweb/Renderer/VertexArray.h"
#include "Cobweb/Renderer/UniformBuffer.h"

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
		float vertices[] = {
			 0.0f,  0.0f, 0.0f,
			 1.0f,  0.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
		};
		Ref<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout({
			{ ShaderDataType::Float3, "Pos" }
			});

		uint32_t indices[] = {
			0, 1, 2
		};
		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		Ref<VertexArray> vao = VertexArray::Create();
		vao->AddVertexBuffer(vbo);
		vao->SetIndexBuffer(ibo);

		Ref<UniformBuffer> ubo = UniformBuffer::Create(4 * sizeof(float), 0);
		ubo->SetData(glm::value_ptr(m_Color), 4 * sizeof(float));

		Ref<Shader> shader = Shader::Create("Base", "assets/shaders/.bin/Base_vertex.spv", "assets/shaders/.bin/Base_pixel.spv");

		while (m_Running)
		{
			glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			ubo->SetData(glm::value_ptr(m_Color), 4 * sizeof(float));
			vao->Bind();
			glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);

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
