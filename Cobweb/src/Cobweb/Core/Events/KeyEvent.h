#pragma once

#include "Event.h"

#include "Cobweb/Core/KeyCodes.h"

namespace Cobweb
{
	class KeyEvent : public Event
	{
	public:
		virtual ~KeyEvent() = default;

		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategory_Keyboard | EventCategory_Input);

	protected:
		KeyEvent(KeyCode keyCode)
			: m_KeyCode(keyCode)
		{}

	protected:
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{}

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
		KeyReleasedEvent(KeyCode keyCode)
			: KeyEvent(keyCode)
		{}

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
		KeyTypedEvent(KeyCode codePoint)
			: KeyEvent(codePoint)
		{}

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
