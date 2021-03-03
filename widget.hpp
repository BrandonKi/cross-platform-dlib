#ifndef __WIDGET_H
#define __WIDGET_H

#include <string>

// pure virtual class!
class Widget {

public:
    virtual std::string message(void) = 0; // pure virtual func

};

#endif
