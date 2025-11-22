#ifndef API__MACRO_EXPORTS__MACRO_EXPORTS__HPP
#define API__MACRO_EXPORTS__MACRO_EXPORTS__HPP


#if defined(ANDROMEDA_API_BUILD)
	// building the DLL
	#define ANDROMEDA_API __declspec(dllexport)
#elif defined(ANDROMEDA_API_USE_DLL)
	// using the DLL
	#define ANDROMEDA_API __declspec(dllimport)
#else
	// static lib or no dll semantics
	#define ANDROMEDA_API
#endif


#endif // API_MACRO_EXPORTS__MACRO_EXPORTS__HPP