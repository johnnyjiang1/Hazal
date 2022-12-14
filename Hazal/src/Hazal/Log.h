#pragma once

#include "Core.h"
#include "spdlog\spdlog.h"

namespace Hazal {
	class HAZAL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define HAZAL_CORE_FATAL(...)		::Hazal::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define HAZAL_CORE_ERROR(...)		::Hazal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HAZAL_CORE_WARN(...)		::Hazal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HAZAL_CORE_INFO(...)		::Hazal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HAZAL_CORE_TRACE(...)		::Hazal::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define HAZAL_CLIENT_FATAL(...)		::Hazal::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define HAZAL_CLIENT_ERROR(...)		::Hazal::Log::GetClientLogger()->error(__VA_ARGS__)
#define HAZAL_CLIENT_WARN(...)		::Hazal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HAZAL_CLIENT_INFO(...)		::Hazal::Log::GetClientLogger()->info(__VA_ARGS__)
#define HAZAL_CLIENT_TRACE(...)		::Hazal::Log::GetClientLogger()->trace(__VA_ARGS__)