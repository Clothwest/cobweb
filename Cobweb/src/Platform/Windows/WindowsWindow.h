#pragma once

#include "Cobweb/Core/Window.h"

#include "Cobweb/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

#include <utility>

namespace Cobweb
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps &props);
		~WindowsWindow();

		void OnUpdate() override;

		inline void *GetNativeWindow() const override { return m_Window; }

		inline int GetWidth() const override { return m_Data.Width; }
		inline int GetHeight() const override { return m_Data.Height; }
		inline std::pair<int, int> GetDisplaySize() const override { return { m_Data.Width, m_Data.Height }; }

		void SetVSync(bool enabled) override;
		inline bool IsVSync() const override { return m_Data.VSync; }

		inline void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }

	private:
		static void OnWindowClosed(GLFWwindow *window);
		static void OnWindowResized(GLFWwindow *window, int width, int height);
		static void OnWindowMoved(GLFWwindow *window, int xPos, int yPos);
		// WindowFocused and WindowLostFocus
		static void OnWindowFocusEvent(GLFWwindow *window, int focused);

		// KeyPress and KeyRelease
		static void OnKeyEvent(GLFWwindow *window, int keyCode, int scanCode, int action, int mods);
		static void OnKeyTyped(GLFWwindow *window, unsigned int codePoint);

		static void OnMouseMoved(GLFWwindow *window, double xPos, double yPos);
		// MouseButtonPressed and MouseButtonRelease
		static void OnMouseButtonEvent(GLFWwindow *window, int button, int action, int mods);
		static void OnMouseScrolled(GLFWwindow *window, double xOffset, double yOffset);

	private:
		GLFWwindow *m_Window;
		GraphicsContext *m_Context;

		struct WindowData
		{
			std::string Title;
			int Width, Height;
			bool VSync = true;

			EventCallbackFn EventCallback;

			WindowData(const WindowProps &props)
				: Title(props.Title), Width(props.Width), Height(props.Height)
			{
			}
		};
		WindowData m_Data;

		friend WindowData &GetWindowData(GLFWwindow *window);
	};
}
