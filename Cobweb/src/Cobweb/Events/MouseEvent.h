#pragma once

#include "Event.h"

namespace Cobweb
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int xPos, int yPos)
			: m_XPos(xPos), m_YPos(yPos)
		{
		}

		~MouseMovedEvent() = default;

		inline int GetXPos() const { return m_XPos; }
		inline int GetYPos() const { return m_YPos; }
		inline std::pair<int, int> GetPos() const { return { m_XPos, m_YPos }; }

		inline std::string ToString() const
		{
			std::stringstream ss;
			ss << GetName() << ": (" << m_XPos << ", " << m_YPos << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input);

	private:
		EVENT_CLASS_TYPE(MouseMoved);

	private:
		int m_XPos, m_YPos;
	};

	class MouseButtonEvent : public Event
	{
	public:
		~MouseButtonEvent() = default;

		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_MouseButton | EventCategory_Input);

	protected:
		MouseButtonEvent(int button)
			: m_Button(button)
		{
		}

	protected:
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{
		}

		~MouseButtonPressedEvent() = default;

		inline std::string ToString() const
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

	private:
		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{
		}

		~MouseButtonReleasedEvent() = default;

		inline std::string ToString() const
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

	private:
		EVENT_CLASS_TYPE(MouseButtonReleased);
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int xOffset, int yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}

		~MouseScrolledEvent() = default;

		inline int GetXOffset() const { return m_XOffset; }
		inline int GetYOffset() const { return m_YOffset; }
		inline std::pair<int, int> GetOffset() const { return { m_XOffset, m_YOffset }; }

		inline std::string ToString() const
		{
			std::stringstream ss;
			ss << GetName() << ": (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input);

	private:
		EVENT_CLASS_TYPE(MouseScrolled);

	private:
		int m_XOffset, m_YOffset;
	};
}
