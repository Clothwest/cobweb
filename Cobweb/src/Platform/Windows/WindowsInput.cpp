#include "cwpch.h"

#include "Cobweb/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Cobweb
{
	static GLFWwindow *s_GetWindow();

	bool Input::IsKeyPressed(KeyCode key)
	{
		GLFWwindow *window = s_GetWindow();
		int state = glfwGetKey(window, (int)key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	float Input::GetMouseX()
	{
		const auto [xPos, _] = GetMousePos();
		return xPos;
	}

	float Input::GetMouseY()
	{
		const auto [_, yPos] = GetMousePos();
		return yPos;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		GLFWwindow *window = s_GetWindow();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		return { (float)xPos, (float)(height - yPos) };
	}

	bool Input::IsMouseButtonPressed(MouseButton button)
	{
		GLFWwindow *window = s_GetWindow();
		int state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	GLFWwindow *s_GetWindow()
	{
		return glfwGetCurrentContext();
	}
}
