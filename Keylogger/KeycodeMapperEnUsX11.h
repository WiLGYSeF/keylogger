#ifndef KEYCODE_MAPPER_EN_US_X11_H
#define KEYCODE_MAPPER_EN_US_X11_H

#ifdef __linux__

#include "KeycodeMapperEnUs.h"

#include <iostream>

namespace Keylogger {

class KeycodeMapperEnUsX11 : public Keylogger::KeycodeMapperEnUs {
 public:
    std::string keycodeToStr(int keycode, bool modifierShift);

    bool isCtrl(int keycode);
    bool isShift(int keycode);
};

}

#endif // defined(__linux__)

#endif // KEYCODE_MAPPER_EN_US_X11_H
