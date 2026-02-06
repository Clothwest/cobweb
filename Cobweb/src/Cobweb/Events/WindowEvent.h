#pragma once

#include "Event.h"

#include <utility>

namespace Cobweb
{
	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;
		~WindowClosedEvent() = default;

		EVENT_CLASS_CATEGORY(EventCategory_Window);

	private:
		EVENT_CLASS_TYPE(WindowClosed);
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int width, int height)
			: m_Width(width), m_Height(height)
		{
		}

		~WindowResizedEvent() = default;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline std::pair<int, int> GetDisplaySize() const { return { m_Width, m_Height }; }

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategory_Window);

	private:
		EVENT_CLASS_TYPE(WindowResized);

	private:
		int m_Width, m_Height;
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int x, int y)
			: m_XPos(x), m_YPos(y)
		{
		}

		~WindowMovedEvent() = default;

		inline int GetXPos() const { return m_XPos; }
		inline int GetYPos() const { return m_YPos; }
		inline std::pair<int, int> GetPos() const { return { m_XPos, m_YPos }; }

		inline std::string ToString() const
		{
			std::stringstream ss;
			ss << GetName() << ": (" << m_XPos << ", " << m_YPos << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategory_Window);

	private:
		EVENT_CLASS_TYPE(WindowMoved);

	private:
		int m_XPos, m_YPos;
	};

	class WindowFocusedEvent : public Event
	{
	public:
		WindowFocusedEvent() = default;
		~WindowFocusedEvent() = default;

		EVENT_CLASS_CATEGORY(EventCategory_Window);

	private:
		EVENT_CLASS_TYPE(WindowFocused);
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;
		~WindowLostFocusEvent() = default;

		EVENT_CLASS_CATEGORY(EventCategory_Window);

	private:
		EVENT_CLASS_TYPE(WindowLostFocus);
	};
}
