# cross-platform-dll


Load dynamic libraries at runtime to be used as a "loadable module" of sorts. This is all done through a common interface regardless of operating system(only works on linux and windows so far). Also there is a C interface as well as a C++ interface.

## C++ Example
```cpp
dlib lib("./libwidget1.so");

typedef void* (*func)();
func f = reinterpret_cast<func>(lib.get_func("factory"));

lib.close_lib();
```

## C Example
```c
//dlib_handle is defined in the header file
dlib_handle handle = load_lib("./libwidget1.so");

typedef void* (*func)();
func f = (func) get_func(handle, "factory");

close_lib(handle);
```

There is also a more complete example in test/


The only reason this was made is to help with these two projects and a potential future project

https://github.com/BrandonKi/ARCANE

https://github.com/BrandonKi/BF-Compiler