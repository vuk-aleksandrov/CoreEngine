#if defined(_WIN32)
#define DLL_IMPORT __declspec(dllimport)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_IMPORT
#define DLL_EXPORT
#endif

#ifdef CORE_STATIC
#define CORE_API
#else
#ifdef CORE_DLL_EXPORTS
#define CORE_API DLL_EXPORT
#else
#define CORE_API DLL_IMPORT
#endif
#endif