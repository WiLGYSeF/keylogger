#ifndef LOGGER_H
#define LOGGER_H

#include "KeyState.h"

#include <iostream>

namespace Keylogger {

class ILogger {
 public:
    virtual bool open(std::string filename) = 0;
    virtual void close() = 0;

    virtual void logKeycode(int keycode, KeyState state) = 0;
};

}

#endif // LOGGER_H
