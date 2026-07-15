#pragma once

#include "Event.h"

namespace Cobweb
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float xPos, float yPos)
			: m_XPos(xPos), m_YPos(yPos)
		{
		}

		~MouseMovedEvent() = default;

		inline float GetXPos() const { return m_XPos; }
		inline float GetYPos() const { return m_YPos; }
		inline std::pair<float, float> GetPos() const { return { m_XPos, m_YPos }; }

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": (" << m_XPos << ", " << m_YPos << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input);
		EVENT_CLASS_TYPE(MouseMoved);

	private:
		float m_XPos, m_YPos;
	};

	class MouseButtonEvent : public Event
	{
	public:
		virtual ~MouseButtonEvent() = default;

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

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

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

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}

		~MouseScrolledEvent() = default;

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }
		inline std::pair<float, float> GetOffset() const { return { m_XOffset, m_YOffset }; }

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input);
		EVENT_CLASS_TYPE(MouseScrolled);

	private:
		float m_XOffset, m_YOffset;
	};
}
