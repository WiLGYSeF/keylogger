#ifndef KEYSTROKE_CAPTURER
#define KEYSTROKE_CAPTURER

#include <functional>

namespace Keylogger {

enum class KeyState {
    Released,
    Pressed
};

class IKeystrokeCapturer {
 public:
    virtual bool start() = 0;
    virtual void stop() = 0;

    virtual void consumeKeystrokes(bool consume) = 0;
    virtual void setCallback(std::function<void(int keycode, KeyState state)> callback) = 0;
};

}

#endif // KEYSTROKE_CAPTURER
