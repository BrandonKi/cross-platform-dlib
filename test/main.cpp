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
#include "../dlib.h"

#if defined(OS_LINUX)
typedef void* dlib_handle;
#define TCHAR char
#define TEXT(x) x
#elif defined(OS_WINDOWS)
typedef HINSTANCE dlib_handle;
#elif defined(OS_MAC)
#else
#endif

int main(int argc, char **argv) {

    // load the lib
    #ifdef OS_WINDOWS
    dlib lib(TEXT("./widget1.dll"));
    #else
    dlib_handle handle1 = load_lib(TEXT("./libwidget1.so"));
    #endif
    // instanitate/contruct an instance of the class
    // typedef Widget* (*factory)();

    Widget* widget1 = (reinterpret_cast<Widget*(*)()>(lib.get_func("factory")))();
    

    // call member function
    std::cout << widget1->message() << std::endl;

    // close lib
    lib.close();
}