#ifndef API__MACRO_EXPORTS__MACRO_EXPORTS__HPP
#define API__MACRO_EXPORTS__MACRO_EXPORTS__HPP


#if defined(_WIN32) || defined(__CYGWIN__)
    #if defined(ANDROMEDA_API_BUILD)
        #define ANDROMEDA_API __declspec(dllexport)
    #elif defined(ANDROMEDA_API_USE_DLL)
        #define ANDROMEDA_API __declspec(dllimport)
    #else
        #define ANDROMEDA_API
    #endif
#else
    // GCC/Clang (Linux, macOS)
    // Only needed for shared libs; harmless otherwise.
    #if defined(ANDROMEDA_API_BUILD) || defined(ANDROMEDA_API_USE_DLL)
        #define ANDROMEDA_API __attribute__((visibility("default")))
    #else
        #define ANDROMEDA_API
    #endif
#endif

#endif // API_MACRO_EXPORTS__MACRO_EXPORTS__HPP