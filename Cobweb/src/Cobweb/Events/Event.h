#pragma once

#include "Cobweb/Core/Core.h"

#include "Cobweb/Core/Log.h"

#include <string>
#include <string_view>
#include <sstream>
#include <utility>
#include <functional>
#include <type_traits>

namespace Cobweb
{
	enum class EventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowMoved, WindowFocused, WindowLostFocus,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,

		EventCategory_Window = BIT(0),
		EventCategory_Keyboard = BIT(1),
		EventCategory_Mouse = BIT(2),

		EventCategory_MouseButton = BIT(3),

		EventCategory_Input = BIT(4)
	};

	class Event
	{
		friend class EventDispatcher;

	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual int GetEventCategoryFlags() const = 0;

		virtual const char *GetName() const = 0;

		virtual inline std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const { return GetEventCategoryFlags() & category; }

		inline void Handle() { m_Handled = true; }
		inline bool IsHandled() const { return m_Handled; }

	protected:
		Event() = default;

	private:
		bool m_Handled = false;
	};

#define EVENT_CLASS_TYPE(type) inline static EventType GetStaticType() { return EventType::type; } inline EventType GetEventType() const override { return GetStaticType(); } inline const char *GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) inline int GetEventCategoryFlags() const override { return category; }

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T &)>;

	public:
		EventDispatcher(Event &e)
			: m_Event(e)
		{
		}

		~EventDispatcher() = default;

		template <typename T>
		inline bool Dispatch(const EventFn<T> &func)
		{
			if (!m_Event.m_Handled && m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T *)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event &m_Event;
	};
}

template <typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<Cobweb::Event, T>, char>> : public formatter<std::string_view>
{
	format_context::iterator format(const T &e, format_context &ctx) const
	{
		return formatter<std::string_view>::format(e.ToString(), ctx);
	}
};
