#include "SandboxListener.h"

#include <cstring>

#define SANDBOX_SEQ_LEN 8

namespace Keylogger {

std::string generateKeySeq() {
    static char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char seq[SANDBOX_SEQ_LEN + 1];
    size_t sz = strlen(chars);

    for (int i = 0; i < SANDBOX_SEQ_LEN; i++) {
        seq[i] = chars[rand() % sz];
    }
    seq[SANDBOX_SEQ_LEN] = 0;

    return std::string(seq);
}

void SandboxListener::start(IKeycodeMapper* mapper) {
    _mapper = mapper;
    _sandboxExitSeq = generateKeySeq();
}

bool SandboxListener::keycodeSent(int keycode) {
    std::string key = _mapper->keycodeToStr(keycode, false);

    if (key.length() == 1 && key[0] == _sandboxExitSeq[_seqIndex]) {
        _seqIndex++;
        if (_seqIndex == _sandboxExitSeq.length()) {
            _seqIndex = 0;
            return true;
        }
        return false;
    }

    _seqIndex = 0;
    return false;
}

std::string SandboxListener::getExitSeq(bool remaining) {
    return remaining ? _sandboxExitSeq.substr(_seqIndex) : _sandboxExitSeq;
}

}
