#include "StdAfx.h"
#include "WindowsKeyboardBackend.h"
#include "WindowsKeyMapper.h"  // mapping VK_ to KeyCode

WindowsKeyboardBackend::WindowsKeyboardBackend() {}
WindowsKeyboardBackend::~WindowsKeyboardBackend() {}

void WindowsKeyboardBackend::update(KeyboardState& state) {
    // Reset semua state dulu
    state.clear();

    // Loop semua virtual key (0–255)
    for (int vk = 0; vk <= 255; ++vk) {
        SHORT keyState = GetAsyncKeyState(vk);
        if (keyState & 0x8000) {
            KeyCode code = MapWindowsKey(vk);
            if (code != Key_UNKNOWN) {
                state.pressKey(code);
            }
        }
    }
}