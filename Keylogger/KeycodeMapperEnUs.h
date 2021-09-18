#ifndef KEYCODE_MAPPER_US_H
#define KEYCODE_MAPPER_US_H

#include "IKeycodeMapper.h"

#include <iostream>

#define VK_BACK			0x08
#define VK_TAB			0x09
#define VK_RETURN		0x0d
#define VK_SHIFT		0x10
#define VK_CONTROL		0x11
#define VK_MENU			0x12
#define VK_PAUSE		0x13
#define VK_CAPITAL		0x14
#define VK_HANGUEL		0x15
#define VK_HANJA		0x19
#define VK_ESCAPE		0x1b
#define VK_SPACE		0x20
#define VK_PRIOR		0x21
#define VK_NEXT			0x22
#define VK_END			0x23
#define VK_HOME			0x24
#define VK_LEFT			0x25
#define VK_UP			0x26
#define VK_RIGHT		0x27
#define VK_DOWN			0x28
#define VK_SNAPSHOT		0x2c
#define VK_INSERT		0x2d
#define VK_DELETE		0x2e
#define VK_HELP			0x2f
#define VK_LWIN			0x5b
#define VK_RWIN			0x5c
#define VK_APPS			0x5d
#define VK_NUMPAD0		0x60
#define VK_NUMPAD1		0x61
#define VK_NUMPAD2		0x62
#define VK_NUMPAD3		0x63
#define VK_NUMPAD4		0x64
#define VK_NUMPAD5		0x65
#define VK_NUMPAD6		0x66
#define VK_NUMPAD7		0x67
#define VK_NUMPAD8		0x68
#define VK_NUMPAD9		0x69
#define VK_MULTIPLY		0x6a
#define VK_ADD			0x6b
#define VK_SUBTRACT		0x6d
#define VK_DECIMAL		0x6e
#define VK_DIVIDE		0x6f
#define VK_F1			0x70
#define VK_F2			0x71
#define VK_F3			0x72
#define VK_F4			0x73
#define VK_F5			0x74
#define VK_F6			0x75
#define VK_F7			0x76
#define VK_F8			0x77
#define VK_F9			0x78
#define VK_F10			0x79
#define VK_F11			0x7a
#define VK_F12			0x7b
#define VK_F13			0x7c
#define VK_F14			0x7d
#define VK_F15			0x7e
#define VK_F16			0x7f
#define VK_F17			0x80
#define VK_F18			0x81
#define VK_F19			0x82
#define VK_F20			0x83
#define VK_F21			0x84
#define VK_F22			0x85
#define VK_F23			0x86
#define VK_F24			0x87
#define VK_NUMLOCK		0x90
#define VK_SCROLL		0x91
#define VK_LSHIFT		0xa0
#define VK_RSHIFT		0xa1
#define VK_LCONTROL		0xa2
#define VK_RCONTROL		0xa3
#define VK_LMENU		0xa4
#define VK_RMENU		0xa5
#define VK_VOLUME_MUTE	0xad
#define VK_VOLUME_DOWN	0xae
#define VK_VOLUME_UP	0xaf
#define VK_OEM_1		0xba // ;:
#define VK_OEM_PLUS		0xbb
#define VK_OEM_COMMA	0xbc
#define VK_OEM_MINUS	0xbd
#define VK_OEM_PERIOD	0xbe
#define VK_OEM_2		0xbf // /?
#define VK_OEM_3		0xc0 // `~
#define VK_OEM_4		0xdb // [{
#define VK_OEM_5		0xdc // \|
#define VK_OEM_6		0xdd // ]}
#define VK_OEM_7		0xde // '"

namespace Keylogger {

class KeycodeMapperEnUs : public Keylogger::IKeycodeMapper {
 public:
    std::string keycodeToStr(int keycode, bool modifierShift);

    bool isCtrl(int keycode);
    bool isShift(int keycode);
};

}

#endif // KEYCODE_MAPPER_US_H
