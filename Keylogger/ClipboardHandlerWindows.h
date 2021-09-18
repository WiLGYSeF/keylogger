#ifndef CLIPBOARD_HANDLER_WINDOWS_H
#define CLIPBOARD_HANDLER_WINDOWS_H

#ifdef _WIN32

#include "IClipboardHandler.h"

namespace Keylogger {

class ClipboardHandlerWindows : public IClipboardHandler {
 public:
    std::string getClipboardString();
};

}

#endif // defined(_WIN32)

#endif // CLIPBOARD_HANDLER_WINDOWS_H
