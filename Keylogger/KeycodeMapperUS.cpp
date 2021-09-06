#include "KeycodeMapperUS.h"

#include <string>

namespace Keylogger {

std::string KeycodeMapperUS::keycodeToStr(int keycode) {
    switch (keycode) {
    case VK_BACK:
        return "BKSP";
    case VK_TAB:
        return "TAB";
    case VK_RETURN:
        return "ENTER";
    case VK_SHIFT:
        return "SHIFT";
    case VK_CONTROL:
        return "CTRL";
    case VK_MENU:
        return "ALT";
    case VK_PAUSE:
        return "PAUSE";
    case VK_CAPITAL:
        return "CAPSLOCK";
    case VK_HANGUEL:
        break;
    case VK_HANJA:
        break;
    case VK_ESCAPE:
        return "ESC";
    case VK_SPACE:
        return " ";
    case VK_PRIOR:
        return "PAGE UP";
    case VK_NEXT:
        return "PAGE DN";
    case VK_END:
        return "END";
    case VK_HOME:
        return "HOME";
    case VK_LEFT:
        return "LEFT";
    case VK_UP:
        return "UP";
    case VK_RIGHT:
        return "RIGHT";
    case VK_DOWN:
        return "DOWN";
    case VK_SNAPSHOT:
        return "PRINTSCREEN";
    case VK_INSERT:
        return "INSERT";
    case VK_DELETE:
        return "DELETE";
    case VK_HELP:
        break;
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
    case VK_LWIN:
    case VK_RWIN:
        return "WIN";
    case VK_APPS:
        return "MENU";
    case VK_NUMPAD0:
    case VK_NUMPAD1:
    case VK_NUMPAD2:
    case VK_NUMPAD3:
    case VK_NUMPAD4:
    case VK_NUMPAD5:
    case VK_NUMPAD6:
    case VK_NUMPAD7:
    case VK_NUMPAD8:
    case VK_NUMPAD9:
        return std::string(1, keycode - VK_NUMPAD0 + '0');
    case VK_MULTIPLY:
        return "*";
    case VK_ADD:
        return "+";
    case VK_SUBTRACT:
        return "-";
    case VK_DECIMAL:
        return ".";
    case VK_DIVIDE:
        return "/";
    case VK_F1:
    case VK_F2:
    case VK_F3:
    case VK_F4:
    case VK_F5:
    case VK_F6:
    case VK_F7:
    case VK_F8:
    case VK_F9:
    case VK_F10:
    case VK_F11:
    case VK_F12:
    case VK_F13:
    case VK_F14:
    case VK_F15:
    case VK_F16:
    case VK_F17:
    case VK_F18:
    case VK_F19:
    case VK_F20:
    case VK_F21:
    case VK_F22:
    case VK_F23:
    case VK_F24:
        return "F" + std::to_string(keycode - VK_F1 + 1);
    case VK_NUMLOCK:
        return "NUMLOCK";
    case VK_SCROLL:
        return "SCROLLLOCK";
    case VK_LSHIFT:
    case VK_RSHIFT:
        return "SHIFT";
    case VK_LCONTROL:
    case VK_RCONTROL:
        return "CTRL";
    case VK_LMENU:
    case VK_RMENU:
        return "ALT";
    case VK_VOLUME_MUTE:
        return "VOL MUTE";
    case VK_VOLUME_DOWN:
        return "VOL DOWN";
    case VK_VOLUME_UP:
        return "VOL UP";
    case VK_OEM_1: // ;:
        return ";";
    case VK_OEM_PLUS:
        return "+";
    case VK_OEM_COMMA:
        return ",";
    case VK_OEM_MINUS:
        return "-";
    case VK_OEM_PERIOD:
        return ".";
    case VK_OEM_2: // /?
        return "/";
    case VK_OEM_3: // `~
        return "`";
    case VK_OEM_4: // [{
        return "[";
    case VK_OEM_5: // \|
        return "\\";
    case VK_OEM_6: // ]}
        return "]";
    case VK_OEM_7: // '"
        return "'";
    default:
        break;
    }
    return "{" + std::to_string(keycode) + "}";
}

bool KeycodeMapperUS::isShiftConsumed(int keycode) {
    return false;
}

bool KeycodeMapperUS::isModifier(int keycode) {
    return false;
}

}
