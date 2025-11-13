#ifndef PHYSICAL_PROPERTIES__MACRO_EXPORTS__HPP
#define PHYSICAL_PROPERTIES__MACRO_EXPORTS__HPP


#if defined(_WIN32)
    #if defined(PHYSICAL_PROPERTIES_EXPORT)
        #define PHYSICAL_PROPERTIES_API __declspec(dllexport)
    #else
        #define PHYSICAL_PROPERTIES_API __declspec(dllimport)
    #endif /* PHYSICAL_PROPERTIES_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define PHYSICAL_PROPERTIES_API __attribute__((visibility("default")))
#endif


#endif // PHYSICAL_PROPERTIES__MACRO_EXPORTS__HPP