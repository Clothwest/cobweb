#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace Cobweb
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define CW_CORE_TRACE(...)     ::Cobweb::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CW_CORE_INFO(...)      ::Cobweb::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CW_CORE_WARN(...)      ::Cobweb::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CW_CORE_ERROR(...)     ::Cobweb::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CW_CORE_CRITICAL(...)  ::Cobweb::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CW_TRACE(...)          ::Cobweb::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CW_INFO(...)           ::Cobweb::Log::GetClientLogger()->info(__VA_ARGS__)
#define CW_WARN(...)           ::Cobweb::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CW_ERROR(...)          ::Cobweb::Log::GetClientLogger()->error(__VA_ARGS__)
#define CW_CRITICAL(...)       ::Cobweb::Log::GetClientLogger()->critical(__VA_ARGS__)

#define CW_CORE_ASSERT(x, ...)  { if (!(x)) { CW_CORE_CRITICAL("(Assertion Failed) " __VA_ARGS__); __debugbreak(); } }
#define CW_ASSERT(x, ...)       { if (!(x)) { CW_CRITICAL("(Assertion Failed) " __VA_ARGS__); __debugbreak(); } }
