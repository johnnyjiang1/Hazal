#pragma once

#include <memory>

#ifdef _WIN32
#ifdef _WIN64
#define HAZAL_PLATFORM_WINDOWS
#else
#error "x86 builds are not supported"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargeConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported"
#elif TARGET_OS_PHONE == 1
#define HAZAL_PLATFORM_IOS
#error "IOS is not supported"
#elif TARGET_OS_MAC == 1
#define HAZAL_PLATFORM_MACOS
#error "MacOS is not supported"
#else
#error "Unknown Apple platform"
#endif
#elif defined(__ANDROID__)
#define HAZAL_PLATFORM_ANDROID
#error "Android is not supported"
#elif defined(__LINUX__)
#error "Linux is not supported"
#else
#error "Unknown pltform"
#endif

#ifdef HAZAL_PLATFORM_WINDOWS
#ifdef HAZAL_DYNAMIC_LINK
#ifdef HAZAL_BUILD_DLL
#define HAZAL_API __declspec(dllexport)
#else
#define HAZAL_API __declspec(dllimport)
#endif
#else
#define HAZAL_API
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

namespace Hazal {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}