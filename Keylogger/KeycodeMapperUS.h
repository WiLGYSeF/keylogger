#ifndef KEYCODE_MAPPER_US_H
#define KEYCODE_MAPPER_US_H

#include "IKeycodeMapper.h"

#include <iostream>

namespace Keylogger {

class KeycodeMapperUS : public Keylogger::IKeycodeMapper {
 public:
    std::string keycodeToStr(int keycode);
    bool isShiftConsumed(int keycode);
    bool isModifier(int keycode);
};

}

#endif // KEYCODE_MAPPER_US_H
