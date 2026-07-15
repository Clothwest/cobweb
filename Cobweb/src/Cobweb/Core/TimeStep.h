#pragma once

#include "Cobweb/Core/Log.h"

#include <string>
#include <string_view>
#include <sstream>
#include <type_traits>

namespace Cobweb
{
	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			: m_Time(time)
		{}

		~TimeStep() = default;

		inline std::string ToString() const
		{
			std::stringstream ss;
			ss << GetSeconds() << "s\t(" << GetMilliseconds() << "ms)";
			return ss.str();
		}

		inline operator float() const { return m_Time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}

template<>
struct fmt::formatter<Cobweb::TimeStep> : public formatter<std::string_view>
{
	format_context::iterator format(Cobweb::TimeStep ts, format_context &ctx) const
	{
		return formatter<std::string_view>::format(ts.ToString(), ctx);
	}
};
