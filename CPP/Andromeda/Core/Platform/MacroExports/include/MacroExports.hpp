#ifndef PLATFORM__MACRO_EXPORTS__HPP
#define PLATFORM__MACRO_EXPORTS__HPP


#if defined(_WIN32)
    #if defined(PLATFORM_EXPORT)
        #define PLATFORM_API __declspec(dllexport)
    #else
        #define PLATFORM_API __declspec(dllimport)
    #endif /* PLATFORM_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define PLATFORM_API __attribute__((visibility("default")))
#endif


#endif // PLATFORM__MACRO_EXPORTS__HPP