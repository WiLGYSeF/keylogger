#ifndef KEYSTROKE_CAPTURER
#define KEYSTROKE_CAPTURER

namespace Keylogger {

class IKeystrokeCapturer {
 public:
    virtual bool start() = 0;
    virtual void stop() = 0;

    virtual void consumeKeystrokes(bool consume) = 0;
};

}

#endif // KEYSTROKE_CAPTURER
