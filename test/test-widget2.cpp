#include <string>
#include "./widget.hpp"

class TestWidget2 : public Widget {
public:
    std::string message(void) {
        return "Hello. I'm Test Widget2";
    }
};

DLL_EXPORT extern "C" Widget* factory(void) {
    return static_cast<Widget*>(new TestWidget2);
}
