#include "cwpch.h"
#include "OpenGLContext.h"

#include "Cobweb/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Cobweb
{
	OpenGLContext::OpenGLContext(void *windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CW_CORE_ASSERT(windowHandle, "Window handle is NULL!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent((GLFWwindow *)m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CW_CORE_ASSERT(status, "Could not initialize Glad!");

		CW_CORE_INFO("OpenGL Info:");
		CW_CORE_INFO((const char *)glGetString(GL_VENDOR));
		CW_CORE_INFO((const char *)glGetString(GL_RENDERER));
		CW_CORE_INFO((const char *)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers((GLFWwindow *)m_WindowHandle);
	}
}
