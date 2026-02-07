#include "cwpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

namespace Cobweb
{
	static int s_ToGLFWKey(int keyCode);
	static int s_ToGLFWMouseButton(int button);

	static GLFWwindow *s_GetWindow();

	Input *Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keyCode) const
	{
		GLFWwindow *window = s_GetWindow();
		int state = glfwGetKey(window, s_ToGLFWKey(keyCode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	float WindowsInput::GetMouseXImpl() const
	{
		const auto [xPos, _] = GetMousePosImpl();
		return xPos;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		const auto [_, yPos] = GetMousePosImpl();
		return yPos;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() const
	{
		GLFWwindow *window = s_GetWindow();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		return { (float)xPos, (float)(height - yPos) };
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow *window = s_GetWindow();
		int state = glfwGetMouseButton(window, s_ToGLFWMouseButton(button));
		return state == GLFW_PRESS;
	}

	int s_ToGLFWKey(int keyCode)
	{
		return keyCode;
	}

	int s_ToGLFWMouseButton(int button)
	{
		return button;
	}

	GLFWwindow *s_GetWindow()
	{
		return glfwGetCurrentContext();
	}
}
