#ifndef WINDOW_HANDLER_LINUX_X11_H
#define WINDOW_HANDLER_LINUX_X11_H

#ifdef __linux__

#include "IWindowHandler.h"

namespace Keylogger {

class WindowHandlerLinuxX11 : public IWindowHandler {
 public:
    std::string getWindowString();
};

}

#endif // defined(__linux__)

#endif // WINDOW_HANDLER_LINUX_X11_H
