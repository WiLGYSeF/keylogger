#ifndef STDOUTLOGGER_H
#define STDOUTLOGGER_H

#include "IKeycodeMapper.h"
#include "ILogger.h"

#include <fstream>

namespace Keylogger {

class StdoutLogger : public ILogger {
 public:
    bool open(std::string unused);
    bool open(IKeycodeMapper* mapper);
    void close();

    void logKeycode(int keycode, KeyState state);
 private:
     IKeycodeMapper* _mapper;

     bool _modifierCtrl;
     bool _modifierShift;
};

}

#endif // FILELOGGER_H
