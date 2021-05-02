#pragma once

#ifdef SE_PLATEFORM_WINDOWS
	#ifdef SE_BUILD_DLL
		#define SE_API __declspec(dllexport)
	#else
		#define SE_API __declspec(dllimport)
	#endif
#else
	#error SpringEngine should only run on a Windows machine
#endif

#define SE_CLASS(...)
#define SE_PROPERTY(...)

/*
#ifdef SE_DEBUG
	#define SE_MP(path) std::string buf(path); \
				        buf.append(two);
#else
	#define SE_MP(path);
#endif
*/