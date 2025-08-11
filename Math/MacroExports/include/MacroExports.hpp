#ifndef MATH__MACRO_EXPORTS__HPP
#define MATH__MACRO_EXPORTS__HPP


#if defined(_WIN32)
    #if defined(MATH_EXPORT)
        #define MATH_API __declspec(dllexport)
    #else
        #define MATH_API __declspec(dllimport)
    #endif /* MATH_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define MATH_API __attribute__((visibility("default")))
#endif


#endif // MATH__MACRO_EXPORTS__HPP