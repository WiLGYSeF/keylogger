#ifndef LOGGER_H
#define LOGGER_H

#include "IKeycodeMapper.h"
#include <iostream>

namespace Keylogger {

class ILogger {
 public:
    virtual bool open(IKeycodeMapper &mapper, std::string filename) = 0;
    virtual void close() = 0;

    virtual void logKeycode(int keycode, int state) = 0;
};

}

#endif // LOGGER_H
