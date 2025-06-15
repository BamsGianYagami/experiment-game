#include "StdAfx.h"
#include "WindowsMouseBackend.h"

WindowsMouseBackend::WindowsMouseBackend() {}

WindowsMouseBackend::~WindowsMouseBackend() {}

void WindowsMouseBackend::update(MouseState& state) {
    POINT p;
    GetCursorPos(&p);
    state.x = p.x;
    state.y = p.y;

    state.leftButton   = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    state.rightButton  = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    state.middleButton = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

	state.mouse4Button = (GetAsyncKeyState(VK_XBUTTON1) & 0x8000) != 0;
    state.mouse5Button = (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) != 0;

    // Scroll: bisa implement jika kamu punya sistem message / raw input
    state.scrollDelta = 0;
}