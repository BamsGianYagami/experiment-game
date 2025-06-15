#include "StdAfx.h"
// AndroidKeyMapper.cpp
#include "AndroidKeyMapper.h"

KeyCode MapAndroidKey(int androidKeyCode) {
    switch (androidKeyCode) {
        case 29: return Key_A; // AKEYCODE_A
        case 30: return Key_B;
        case 31: return Key_C;
        case 32: return Key_D;
        case 33: return Key_E;
        case 34: return Key_F;
        case 35: return Key_G;
        case 36: return Key_H;
        case 37: return Key_I;
        case 38: return Key_J;
        case 39: return Key_K;
        case 40: return Key_L;
        case 41: return Key_M;
        case 42: return Key_N;
        case 43: return Key_O;
        case 44: return Key_P;
        case 45: return Key_Q;
        case 46: return Key_R;
        case 47: return Key_S;
        case 48: return Key_T;
        case 49: return Key_U;
        case 50: return Key_V;
        case 51: return Key_W;
        case 52: return Key_X;
        case 53: return Key_Y;
        case 54: return Key_Z;

        case 7:  return Key_0;
        case 8:  return Key_1;
        case 9:  return Key_2;
        case 10: return Key_3;
        case 11: return Key_4;
        case 12: return Key_5;
        case 13: return Key_6;
        case 14: return Key_7;
        case 15: return Key_8;
        case 16: return Key_9;

        case 62: return Key_SPACE;
        case 66: return Key_ENTER;
        case 111: return Key_ESCAPE;
        case 21: return Key_LEFT;
        case 22: return Key_RIGHT;
        case 19: return Key_UP;
        case 20: return Key_DOWN;

        case 59: return Key_LSHIFT;
        case 60: return Key_RSHIFT;
        case 113: return Key_LCTRL;
        case 114: return Key_RCTRL;
        case 57: return Key_LALT;
        case 58: return Key_RALT;

        case 61: return Key_TAB;
        case 67: return Key_BACKSPACE;
        case 115: return Key_CAPSLOCK;

        case 131: return Key_F1;
        case 132: return Key_F2;
        case 133: return Key_F3;
        case 134: return Key_F4;
        case 135: return Key_F5;
        case 136: return Key_F6;
        case 137: return Key_F7;
        case 138: return Key_F8;
        case 139: return Key_F9;
        case 140: return Key_F10;
        case 141: return Key_F11;
        case 142: return Key_F12;

        default: return Key_UNKNOWN;
    }
}
