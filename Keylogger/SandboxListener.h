#ifndef SANDBOX_LISTENER_H
#define SANDBOX_LISTENER_H

#include "IKeycodeMapper.h"

#include <iostream>

namespace Keylogger {

class SandboxListener {
 public:
    void start(IKeycodeMapper* mapper);
    bool keycodeSent(int keycode);

    std::string getExitSeq(bool remaining);

 private:
    IKeycodeMapper* _mapper;
    std::string _sandboxExitSeq;
    size_t _seqIndex;
};

}

#endif // SANDBOX_LISTENER_H