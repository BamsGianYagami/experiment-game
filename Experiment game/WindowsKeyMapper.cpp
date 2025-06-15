#include "StdAfx.h"
#include "WindowsKeyMapper.h"

KeyCode MapWindowsKey(int vkCode) {
    switch (vkCode) {
        case 'A': return Key_A;
        case 'B': return Key_B;
        case 'C': return Key_C;
        case 'D': return Key_D;
        case 'E': return Key_E;
        case 'F': return Key_F;
        case 'G': return Key_G;
        case 'H': return Key_H;
        case 'I': return Key_I;
        case 'J': return Key_J;
        case 'K': return Key_K;
        case 'L': return Key_L;
        case 'M': return Key_M;
        case 'N': return Key_N;
        case 'O': return Key_O;
        case 'P': return Key_P;
        case 'Q': return Key_Q;
        case 'R': return Key_R;
        case 'S': return Key_S;
        case 'T': return Key_T;
        case 'U': return Key_U;
        case 'V': return Key_V;
        case 'W': return Key_W;
        case 'X': return Key_X;
        case 'Y': return Key_Y;
        case 'Z': return Key_Z;

        case '0': return Key_0;
        case '1': return Key_1;
        case '2': return Key_2;
        case '3': return Key_3;
        case '4': return Key_4;
        case '5': return Key_5;
        case '6': return Key_6;
        case '7': return Key_7;
        case '8': return Key_8;
        case '9': return Key_9;

        case VK_SPACE: return Key_SPACE;
        case VK_RETURN: return Key_ENTER;
        case VK_ESCAPE: return Key_ESCAPE;
        case VK_LEFT: return Key_LEFT;
        case VK_RIGHT: return Key_RIGHT;
        case VK_UP: return Key_UP;
        case VK_DOWN: return Key_DOWN;

        case VK_SHIFT: case VK_LSHIFT: return Key_LSHIFT;
        case VK_RSHIFT: return Key_RSHIFT;
        case VK_CONTROL: case VK_LCONTROL: return Key_LCTRL;
        case VK_RCONTROL: return Key_RCTRL;
        case VK_MENU: case VK_LMENU: return Key_LALT;
        case VK_RMENU: return Key_RALT;

        case VK_TAB: return Key_TAB;
        case VK_BACK: return Key_BACKSPACE;
        case VK_CAPITAL: return Key_CAPSLOCK;

        case VK_F1: return Key_F1;
        case VK_F2: return Key_F2;
        case VK_F3: return Key_F3;
        case VK_F4: return Key_F4;
        case VK_F5: return Key_F5;
        case VK_F6: return Key_F6;
        case VK_F7: return Key_F7;
        case VK_F8: return Key_F8;
        case VK_F9: return Key_F9;
        case VK_F10: return Key_F10;
        case VK_F11: return Key_F11;
        case VK_F12: return Key_F12;

        default: return Key_UNKNOWN;
    }
}
