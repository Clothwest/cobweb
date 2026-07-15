#include "cwpch.h"
#include "Window.h"

#include "Cobweb/Core/Log.h"

#include "Cobweb/Core/KeyCodes.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Cobweb
{
	Window *Window::Create(const WindowSpecification &spec)
	{
		return new Window(spec);
	}

	Window::Window(const WindowSpecification &spec)
		: m_Specification(spec)
	{}

	Window::~Window()
	{
		delete m_Context;
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Init()
	{
		m_Data.Title = m_Specification.Title;
		m_Data.Width = m_Specification.Width;
		m_Data.Height = m_Specification.Height;

		CW_CORE_INFO("Creating window '{0}' ({1}, {2}).", m_Specification.Title, m_Specification.Width, m_Specification.Height);

		int success = glfwInit();
		CW_CORE_ASSERT(success, "Could not initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetErrorCallback([](int errorCode, const char *description) {
			CW_CORE_ERROR("GLFW Error ({0}): {1}", errorCode, description);
			});

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, &Window::OnWindowClosed);
		glfwSetWindowSizeCallback(m_Window, &Window::OnWindowResized);
		glfwSetWindowPosCallback(m_Window, &Window::OnWindowMoved);
		glfwSetWindowFocusCallback(m_Window, &Window::OnWindowFocusEvent);

		glfwSetKeyCallback(m_Window, &Window::OnKeyEvent);
		glfwSetCharCallback(m_Window, &Window::OnKeyTyped);

		glfwSetCursorPosCallback(m_Window, &Window::OnMouseMoved);
		glfwSetMouseButtonCallback(m_Window, &Window::OnMouseButtonEvent);
		glfwSetScrollCallback(m_Window, &Window::OnMouseScrolled);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffer();
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Specification.VSync = enabled;
	}

	void Window::OnWindowClosed(GLFWwindow *window)
	{
		WindowData &data = GetWindowData(window);

		WindowClosedEvent event;
		data.EventCallback(event);
	}

	void Window::OnWindowResized(GLFWwindow *window, int width, int height)
	{
		WindowData &data = GetWindowData(window);

		data.Width = width;
		data.Height = height;

		WindowResizedEvent event(width, height);
		data.EventCallback(event);
	}

	void Window::OnWindowMoved(GLFWwindow *window, int xPos, int yPos)
	{
		WindowData &data = GetWindowData(window);

		WindowMovedEvent event(xPos, yPos);
		data.EventCallback(event);
	}

	void Window::OnWindowFocusEvent(GLFWwindow *window, int focused)
	{
		WindowData &data = GetWindowData(window);

		if (focused)
		{
			WindowFocusedEvent event;
			data.EventCallback(event);
		}
		else
		{
			WindowLostFocusEvent event;
			data.EventCallback(event);
		}
	}

	void Window::OnKeyEvent(GLFWwindow *window, int keyCode, int scanCode, int action, int mods)
	{
		WindowData &data = GetWindowData(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event((KeyCode)keyCode, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event((KeyCode)keyCode, 1);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event((KeyCode)keyCode);
				data.EventCallback(event);
				break;
			}
		}
	}

	void Window::OnKeyTyped(GLFWwindow *window, unsigned int codePoint)
	{
		WindowData &data = GetWindowData(window);

		KeyTypedEvent event((KeyCode)codePoint);
		data.EventCallback(event);
	}

	void Window::OnMouseMoved(GLFWwindow *window, double xPos, double yPos)
	{
		WindowData &data = GetWindowData(window);

		MouseMovedEvent event((float)xPos, (float)(data.Height - yPos));
		data.EventCallback(event);
	}

	void Window::OnMouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
	{
		WindowData &data = GetWindowData(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
	}

	void Window::OnMouseScrolled(GLFWwindow *window, double xOffset, double yOffset)
	{
		WindowData &data = GetWindowData(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	}

	Window::WindowData &Window::GetWindowData(GLFWwindow *window)
	{
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
		CW_CORE_ASSERT(data.EventCallback, "Did not bind EventCallback!");
		return data;
	}
}
