# Keylogger

A keylogger and keystroke sandbox written for Windows and Linux X11 environments.

Create a keyboard sandbox that prevents keyboards and programmable keyboard HIDs from interacting with the desktop by capturing keystrokes and logging them to a file.
Useful for debugging keyboards and programmable HIDs without affecting the desktop environment.

Log clipboard data and window names in both Windows and X11 environments.

# Compile

## Compile For Windows

1. Open the project in Visual Studio.
2. Build the project.

## Compile For Linux

1. Install libx11-dev.
2. Run the Makefile.
