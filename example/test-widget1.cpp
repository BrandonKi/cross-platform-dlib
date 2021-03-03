#include <string>
#include "./widget.hpp"

class TestWidget1 : public Widget  {
public:
    std::string message(void) {
        return "Hello. I'm Test Widget1";
    }
};

DLL_EXPORT extern "C" Widget* factory(void) {
    return static_cast<Widget*>(new TestWidget1);
}
