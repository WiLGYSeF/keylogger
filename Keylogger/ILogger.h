#ifndef LOGGER_H
#define LOGGER_H

#include "IClipboardHandler.h"
#include "IKeycodeMapper.h"
#include "IKeystrokeCapturer.h"
#include "IWindowHandler.h"

#include <iostream>

namespace Keylogger {

class ILogger {
 public:
    virtual bool open(std::string filename) = 0;
    virtual bool open(IKeycodeMapper* mapper, std::string filename) = 0;
    virtual bool open(IKeycodeMapper* mapper, IClipboardHandler* clipboardHandler, std::string filename) = 0;
    virtual bool open(
        IKeycodeMapper* mapper,
        IClipboardHandler* clipboardHandler,
        IWindowHandler* windowHandler,
        std::string filename
    ) = 0;

    virtual void close() = 0;

    virtual void logKeycode(int keycode, KeyState state) = 0;
};

}

#endif // LOGGER_H
