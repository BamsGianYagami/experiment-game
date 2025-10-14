#include "StdAfx.h"
#include "WindowsKeyboardBackend.h"
#include "WindowsKeyMapper.h"  // mapping VK_ to KeyCode

WindowsKeyboardBackend::WindowsKeyboardBackend() {
	memset(keyStates, 0, sizeof(keyStates));
}
WindowsKeyboardBackend::~WindowsKeyboardBackend() {}

void WindowsKeyboardBackend::update(KeyboardState &state) {
    state.clear();
    for (int vk = 0; vk <= 255; ++vk) {
        if (keyStates[vk]) {
            KeyCode code = MapWindowsKey(vk);
            if (code != Key_UNKNOWN) {
                state.pressKey(code);
            }
        }
    }
}

void WindowsKeyboardBackend::onKeyDown(WPARAM wParam) {
    if (wParam < 256) {
        keyStates[wParam] = true;
    }
}

void WindowsKeyboardBackend::onKeyUp(WPARAM wParam) {
    if (wParam < 256) {
        keyStates[wParam] = false;
    }
}