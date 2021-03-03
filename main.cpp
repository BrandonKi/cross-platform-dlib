#include <dlfcn.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "./widget.hpp"

typedef void* dynamic_lib_handle;

static dynamic_lib_handle load_lib(const std::string& path);
static Widget* instantiate(const dynamic_lib_handle handle);
static void close_lib(dynamic_lib_handle handle);

int main(int argc, char **argv) {

    // load the lib
    dynamic_lib_handle handle = load_lib("./test-widget1.so");

    // instanitate/contruct an instance of the class
    Widget* widget = instantiate(handle);

    // call member function
    std::cout << widget->message() << std::endl;

    // close lib
    close_lib(handle);
}

static dynamic_lib_handle load_lib(const std::string& path) {
    std::cout << "Trying to open: " << path << std::endl;
    return dlopen(path.data() , RTLD_LAZY);
}

static Widget* instantiate(const dynamic_lib_handle handle) {

    if (handle == nullptr) return nullptr;

    void *maker = dlsym(handle , "factory");

    if (maker == nullptr) return nullptr;

    typedef Widget* (*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

    return func();
}

static void close_lib(dynamic_lib_handle handle) {
    dlclose(handle);
}

