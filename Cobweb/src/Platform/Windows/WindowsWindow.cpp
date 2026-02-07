#include "cwpch.h"
#include "WindowsWindow.h"

#include "Cobweb/Core/Log.h"

#include <glad/glad.h>

namespace Cobweb
{
	Scope<Window> Window::Create(const WindowProps &props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps &props)
		: m_Data(props)
	{
		CW_CORE_INFO("Creating window \"{0}\" ({1}, {2}).", props.Title, props.Width, props.Height);

		int success = glfwInit();
		CW_CORE_ASSERT(success, "Could not initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetErrorCallback([](int errorCode, const char *description) {
			CW_CORE_ERROR("GLFW Error ({0}): {1}", errorCode, description);
			});

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CW_CORE_ASSERT(status, "Could not initialize Glad!");

		CW_CORE_INFO("OpenGL Info:");
		CW_CORE_INFO((const char *)glGetString(GL_VENDOR));
		CW_CORE_INFO((const char *)glGetString(GL_RENDERER));
		CW_CORE_INFO((const char *)glGetString(GL_VERSION));

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Window, &WindowsWindow::OnWindowClosed);
		glfwSetWindowSizeCallback(m_Window, &WindowsWindow::OnWindowResized);
		glfwSetWindowPosCallback(m_Window, &WindowsWindow::OnWindowMoved);
		glfwSetWindowFocusCallback(m_Window, &WindowsWindow::OnWindowFocusEvent);

		glfwSetKeyCallback(m_Window, &WindowsWindow::OnKeyEvent);
		glfwSetCharCallback(m_Window, &WindowsWindow::OnKeyTyped);

		glfwSetCursorPosCallback(m_Window, &WindowsWindow::OnMouseMoved);
		glfwSetMouseButtonCallback(m_Window, &WindowsWindow::OnMouseButtonEvent);
		glfwSetScrollCallback(m_Window, &WindowsWindow::OnMouseScrolled);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	void WindowsWindow::OnWindowClosed(GLFWwindow *window)
	{
		WindowData &data = GetWindowData(window);

		WindowClosedEvent event;
		data.EventCallback(event);
	}

	void WindowsWindow::OnWindowResized(GLFWwindow *window, int width, int height)
	{
		WindowData &data = GetWindowData(window);

		data.Width = width;
		data.Height = height;

		WindowResizedEvent event(width, height);
		data.EventCallback(event);
	}

	void WindowsWindow::OnWindowMoved(GLFWwindow *window, int xPos, int yPos)
	{
		WindowData &data = GetWindowData(window);

		WindowMovedEvent event(xPos, yPos);
		data.EventCallback(event);
	}

	void WindowsWindow::OnWindowFocusEvent(GLFWwindow *window, int focused)
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

	void WindowsWindow::OnKeyEvent(GLFWwindow *window, int keyCode, int scanCode, int action, int mods)
	{
		WindowData &data = GetWindowData(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(keyCode, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(keyCode, 1);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(keyCode);
				data.EventCallback(event);
				break;
			}
		}
	}

	void WindowsWindow::OnKeyTyped(GLFWwindow *window, unsigned int codePoint)
	{
		WindowData &data = GetWindowData(window);

		KeyTypedEvent event(codePoint);
		data.EventCallback(event);
	}

	void WindowsWindow::OnMouseMoved(GLFWwindow *window, double xPos, double yPos)
	{
		WindowData &data = GetWindowData(window);

		MouseMovedEvent event((float)xPos, (float)(data.Height - yPos));
		data.EventCallback(event);
	}

	void WindowsWindow::OnMouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
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

	void WindowsWindow::OnMouseScrolled(GLFWwindow *window, double xOffset, double yOffset)
	{
		WindowData &data = GetWindowData(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	}

	WindowsWindow::WindowData &GetWindowData(GLFWwindow *window)
	{
		WindowsWindow::WindowData &data = *(WindowsWindow::WindowData *)glfwGetWindowUserPointer(window);
		CW_CORE_ASSERT(data.EventCallback, "Did not bind EventCallback!");
		return data;
	}
}
