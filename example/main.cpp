#if defined(unix) || defined(__unix__) || defined(__unix)
#define OS_LINUX
#include <dlfcn.h>
#elif defined(_WIN32)
#define OS_WINDOWS
#include <windows.h>
#elif defined(__APPLE__)
#define OS_MAC
#else
#endif

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "./widget.hpp"

#if defined(OS_LINUX)
typedef void* dlib_handle;
#define TCHAR char
#define TEXT(x) x
#elif defined(OS_WINDOWS)
typedef HINSTANCE dlib_handle;
#elif defined(OS_MAC)
#else
#endif

static dlib_handle load_lib(const TCHAR *path);
static Widget* instantiate(const dlib_handle handle);
static void close_lib(dlib_handle handle);

int main(int argc, char **argv) {

    // load the lib
    dlib_handle handle1 = load_lib(TEXT("./libwidget1.so"));
    dlib_handle handle2 = load_lib(TEXT("./libwidget2.so"));

    // instanitate/contruct an instance of the class
    Widget* widget1 = instantiate(handle1);
    Widget* widget2 = instantiate(handle2);

    // call member function
    std::cout << widget1->message() << std::endl;
    std::cout << widget2->message() << std::endl;

    // close lib
    close_lib(handle1);
    close_lib(handle2);
}

static dlib_handle load_lib(const TCHAR *path) {

    #if defined(OS_LINUX)
    std::cout << "Trying to open: " << path << std::endl;
    return dlopen(path, RTLD_NOW);
    #elif defined(OS_WINDOWS)
    std::wcout << L"Trying to open: " << path << std::endl;
    return LoadLibrary(path);
    #elif defined(OS_MAC)
    #else
    #endif

}

static Widget* instantiate(const dlib_handle handle) {
 
    typedef Widget* (*fptr)();

    if (handle == nullptr) return nullptr;

    #if defined(OS_LINUX)
    void *maker = dlsym(handle , "factory");
    #elif defined(OS_WINDOWS)
    fptr maker = (fptr) GetProcAddress(handle, "factory");
    #elif defined(OS_MAC)
    #else
    #endif

    if (maker == nullptr) return nullptr;

    fptr func = reinterpret_cast<fptr>(maker);

    return func();
}

static void close_lib(dlib_handle handle) {
    #if defined(OS_LINUX)
    dlclose(handle);
    #elif defined(OS_WINDOWS)
    FreeLibrary(handle);
    #elif defined(OS_MAC)
    #else
    #endif
}

