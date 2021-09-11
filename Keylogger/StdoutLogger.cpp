#include "StdoutLogger.h"

namespace Keylogger {

bool StdoutLogger::open(std::string unused) {
    return open(nullptr);
}

bool StdoutLogger::open(IKeycodeMapper* mapper) {
    _mapper = mapper;
    return true;
}

void StdoutLogger::close() {}

void StdoutLogger::logKeycode(int keycode, KeyState state) {
    if (_mapper) {
        if (_mapper->isCtrl(keycode)) {
            _modifierCtrl = state == KeyState::Pressed;
        }
        if (_mapper->isShift(keycode)) {
            _modifierShift = state == KeyState::Pressed;
        }

        if (state == KeyState::Pressed) {
            std::cout << _mapper->keycodeToStr(keycode, _modifierShift);
        }
    }
    else {
        std::cout << keycode << ":" << (state == KeyState::Pressed ? 1 : 0) << " ";
    }
}

}
