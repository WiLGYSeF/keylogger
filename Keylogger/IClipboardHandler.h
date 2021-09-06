#ifndef CLIPBOARD_HANDLER_H
#define CLIPBOARD_HANDLER_H

#include <iostream>

namespace Keylogger {

class IClipboardHandler {
 public:
    virtual std::string getClipboardString() = 0;
};

}

#endif // CLIPBOARD_HANDLER_H