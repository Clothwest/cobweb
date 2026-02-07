#pragma once

#include "Cobweb/Core/Core.h"
#include "Cobweb/Events/Events.h"

#include <functional>
#include <utility>
#include <string>

namespace Cobweb
{
	struct WindowProps
	{
		std::string Title;
		int Width, Height;

		WindowProps()
			: Title("Cobweb Engine"), Width(1280), Height(720)
		{
		}
	};

	class Window
	{
	public:
		static Scope<Window> Create(const WindowProps &props = WindowProps());

	public:
		using EventCallbackFn = std::function<void(Event &)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void *GetNativeWindow() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual std::pair<int, int> GetDisplaySize() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

	protected:
		Window() = default;
	};
}
