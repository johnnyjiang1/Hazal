#pragma once

#ifdef HAZAL_PLATFORM_WINDOWS
	#ifdef HAZAL_BUILD_DLL
		#define HAZAL_API __declspec(dllexport)
	#else
		#define HAZAL_API __declspec(dllimport)
	#endif
#else
	#error Hazal only supports Windows
#endif

#ifdef HAZAL_ENABLE_ASSERTS
	#define HAZAL_CLIENT_ASSERT(x, ...) { if (!(x)) { HAZAL_CLIENT_ERROR("Assertion Failed: {0}, __VA_ARGS__"); __debugbreak();}}
	#define HAZAL_CORE_ASSERT(x, ...) { if (!(x)) { HAZAL_CORE_ERROR("Assertion Failed: {0}, __VA_ARGS__"); __debugbreak();}}
#else
	#define HAZAL_CLIENT_ASSERT(x, ...)
	#define HAZAL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HAZAL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)