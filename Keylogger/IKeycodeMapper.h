#ifndef KEYCODE_MAPPER_H
#define KEYCODE_MAPPER_H

#include <iostream>

namespace Keylogger {

class IKeycodeMapper {
 public:
    virtual std::string keycodeToStr(int keycode) = 0;
    virtual bool isShiftConsumed(int keycode) = 0;
    virtual bool isModifier(int keycode) = 0;
};

}

#endif // KEYCODE_MAPPER_H
