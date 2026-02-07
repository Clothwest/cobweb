#pragma once

#include "Event.h"

namespace Cobweb
{
	class KeyEvent : public Event
	{
	public:
		virtual ~KeyEvent() = default;

		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategory_Keyboard | EventCategory_Input);
		
	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode)
		{
		}

	protected:
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{
		}

		~KeyPressedEvent() = default;

		inline int GetRepeatCount() const { return m_RepeatCount; }

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_KeyCode << " (Repeated: " << m_RepeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{
		}

		~KeyReleasedEvent() = default;

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int codePoint)
			: KeyEvent(codePoint)
		{
		}

		~KeyTypedEvent() = default;

		inline std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};
}
