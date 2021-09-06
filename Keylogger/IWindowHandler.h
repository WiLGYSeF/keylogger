#ifndef WINDOW_HANDLER_H
#define WINDOW_HANDLER_H

#include <iostream>

namespace Keylogger {

class IWindowHandler {
 public:
    virtual std::string getWindowString() = 0;
};

}

#endif // WINDOW_HANDLER_H