#ifndef KEYCODE_MAPPER_H
#define KEYCODE_MAPPER_H

#include <iostream>

namespace Keylogger {

class IKeycodeMapper {
 public:
    virtual std::string keycodeToStr(int keycode, bool modifierShift) = 0;

    virtual bool isCtrl(int keycode) = 0;
    virtual bool isShift(int keycode) = 0;
};

}

#endif // KEYCODE_MAPPER_H
