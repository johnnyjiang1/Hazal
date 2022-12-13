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