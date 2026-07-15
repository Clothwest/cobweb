#pragma once

#include "Cobweb/Core/Base.h"
#include "Cobweb/Core/Events/Events.h"
#include "Cobweb/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <utility>
#include <string>

namespace Cobweb
{
	struct WindowSpecification
	{
		std::string Title = "Cobweb";
		uint32_t Width = 1600, Height = 900;
		bool VSync = false;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event &)>;

	public:
		static Window *Create(const WindowSpecification &spec = WindowSpecification());

	public:
		Window(const WindowSpecification &spec);
		~Window();

		void Init();
		void OnUpdate();

		void *GetNativeWindow() const { return m_Window; }

		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }
		std::pair<uint32_t, uint32_t> GetDisplaySize() const { return { m_Data.Width, m_Data.Height }; }

		void SetVSync(bool enabled);
		bool IsVSync() const { return m_Specification.VSync; }

		void SetEventCallback(const EventCallbackFn &callback) { m_Data.EventCallback = callback; }

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
		WindowSpecification m_Specification;

		GraphicsContext *m_Context;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	private:
		static WindowData &GetWindowData(GLFWwindow *window);
	};
}
