/**
 * @file dlib.h
 * @author Brandon Kirincich
 * @brief see README 
 * 
 * @copyright MIT License
 * 
 */
#if defined(unix) || defined(__unix__) || defined(__unix)
#define OS_LINUX
#include <dlfcn.h>
#elif defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS
#include <windows.h>
#elif defined(__APPLE__) || defined(__MACH__) 
#define OS_MAC
#else
#endif

#if defined(OS_LINUX)
using dlib_handle =  void*;
using TCHAR = char;
#define TEXT(x) x
#elif defined(OS_WINDOWS)
using dlib_handle = HINSTANCE;
#elif defined(OS_MAC)
#else
#endif

#ifdef __cplusplus
class dlib {
    private:
        const TCHAR *m_path;
        dlib_handle m_handle;


    public:

        /**
         * @brief Construct a new dlib object and
         * and load the lib specified by path
         * 
         * @param path relative or absolute path to a dynamic lib
         */
        dlib(const TCHAR *path):
            m_path(path), m_handle()
        {
            m_handle = load_lib();
        }

        ~dlib() = default;

        /**
         * @brief should only be used internally for the C++ version
         * 
         * @param path relative or absolute path to a dynamic lib
         * @return dlib_handle handle to the dynamic lib
         */
        dlib_handle load_lib() {
            #if defined(OS_LINUX)
            return dlopen(m_path, RTLD_NOW);
            #elif defined(OS_WINDOWS)
            return LoadLibrary(m_path);
            #elif defined(OS_MAC)
            #else
            #endif
        }

        /**
         * @brief return a function pointer 
         * to the function specified by func_name
         * 
         * @param func_name name of function to get from dynamic lib
         * @return void* function pointer to the function
         */
        void *get_func(const char *func_name) {
            if (m_handle == nullptr) return nullptr;
            #if defined(OS_LINUX)
            return dlsym(m_handle , func_name);
            #elif defined(OS_WINDOWS)
            return reinterpret_cast<void*>(GetProcAddress(m_handle, func_name));
            #elif defined(OS_MAC)
            #else
            #endif
        }

        /**
         * @brief closes the dynamic lib
         * 
         */
        void close_lib() {
            #if defined(OS_LINUX)
            dlclose(m_handle);
            #elif defined(OS_WINDOWS)
            FreeLibrary(m_handle);
            #elif defined(OS_MAC)
            #else
            #endif
        }
};

#else
/**
 * @brief load the lib specified by path and return for ti
 * 
 * @param path path to a dynamic lib
 * @return dlib_handle handle to the dynamic lib
 */
dlib_handle load_lib(const TCHAR *path) {
    #if defined(OS_LINUX)
    return dlopen(path, RTLD_NOW);
    #elif defined(OS_WINDOWS)
    return LoadLibrary(path);
    #elif defined(OS_MAC)
    #else
    #endif
}

/**
 * @brief return a function pointer to the 
 * function specified by func_name
 * 
 * @param handle handle for a dynamic lib
 * @param func_name name of the funcion to get
 * @return void* function pointer to the function
 */
void *get_func(dlib_handle handle, const char *func_name) {
    if (handle == nullptr) return nullptr;
    #if defined(OS_LINUX)
    return dlsym(handle , func_name);
    #elif defined(OS_WINDOWS)
    return reinterpret_cast<void*>(GetProcAddress(handle, func_name));
    #elif defined(OS_MAC)
    #else
    #endif
}

/**
 * @brief close the dynamic lib
 * 
 * @param handle handle for the dynamic lib
 */
void close_lib(dlib_handle handle) {
    #if defined(OS_LINUX)
    dlclose(handle);
    #elif defined(OS_WINDOWS)
    FreeLibrary(handle);
    #elif defined(OS_MAC)
    #else
    #endif
}

#endif