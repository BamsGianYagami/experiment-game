#include "StdAfx.h"
#ifdef __ANDROID__

#include "AndroidKeyboardBackend.h"
#include "KeyCode.h"  // Enum universal milik engine

AndroidKeyboardBackend::AndroidKeyboardBackend() {}
AndroidKeyboardBackend::~AndroidKeyboardBackend() {}

void AndroidKeyboardBackend::onKeyDown(int androidKeyCode) {
    std::lock_guard<std::mutex> lock(stateMutex);
    KeyCode code = mapAndroidKeyCode(androidKeyCode);
    bufferState.pressKey(code);
}

void AndroidKeyboardBackend::onKeyUp(int androidKeyCode) {
    std::lock_guard<std::mutex> lock(stateMutex);
    KeyCode code = mapAndroidKeyCode(androidKeyCode);
    bufferState.releaseKey(code);
}

void AndroidKeyboardBackend::update(KeyboardState& state) {
    std::lock_guard<std::mutex> lock(stateMutex);
    state = bufferState;
}

KeyCode AndroidKeyboardBackend::mapAndroidKeyCode(int androidKeyCode) {
    switch (androidKeyCode) {
        case 29: return Key_A;
        case 30: return Key_B;
        // ... Lengkapi sesuai kebutuhanmu
        case 66: return Key_ENTER;
        case 62: return Key_SPACE;
        default: return Key_UNKNOWN;
    }
}

#endif  // __ANDROID__
