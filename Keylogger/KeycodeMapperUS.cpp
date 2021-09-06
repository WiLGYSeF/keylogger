#include "KeycodeMapperUS.h"

#include <string>

namespace Keylogger {

std::string KeycodeMapperUS::keycodeToStr(int keycode) {
    switch (keycode) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        return std::string(1, keycode);
    default:
        return "{" + std::to_string(keycode) + "}";
    }
}

bool KeycodeMapperUS::isShiftConsumed(int keycode) {
    return false;
}

bool KeycodeMapperUS::isModifier(int keycode) {
    return false;
}

}
