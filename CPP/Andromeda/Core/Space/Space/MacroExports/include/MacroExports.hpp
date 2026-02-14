#ifndef SPACE__MACRO_EXPORTS__HPP
#define SPACE__MACRO_EXPORTS__HPP


#if defined(_WIN32)
    #if defined(SPACE_EXPORT)
        #define SPACE_API __declspec(dllexport)
    #else
        #define SPACE_API __declspec(dllimport)
    #endif /* SPACE_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define SPACE_API __attribute__((visibility("default")))
#endif


#endif // SPACE__MACRO_EXPORTS__HPP