#ifndef __WIDGET_H
#define __WIDGET_H

#include <string>

#if defined(_WIN32) 
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// pure virtual class
class Widget {

public:
    virtual std::string message(void) = 0; // pure virtual func

};

#endif
