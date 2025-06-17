#pragma once
#include "StdAfx.h"
#include "MouseInputDevice.h"

using namespace GE;
static bool getButtonState(const MouseState& s, MouseButton button) {
    switch (button) {
        case MouseButton_Left:    return s.leftButton;
        case MouseButton_Right:   return s.rightButton;
        case MouseButton_Middle:  return s.middleButton;
        case MouseButton_Mouse4:  return s.mouse4Button;
        case MouseButton_Mouse5:  return s.mouse5Button;
        default:                   return false;
    }
}


MouseInputDevice::MouseInputDevice(IMouseBackend* backend)
    : backend(backend)
{
    std::memset(&state, 0, sizeof(MouseState));
    std::memset(&prevState, 0, sizeof(MouseState));
    std::memset(&delta, 0, sizeof(MouseDeltaState));
}

MouseInputDevice::~MouseInputDevice() {
    // backend tidak dihapus di sini karena bisa dimiliki dari luar
}

void MouseInputDevice::update() {
    if (!backend) return;

    prevState = state;
    backend->update(state);

    delta.deltaX = state.x - prevState.x;
    delta.deltaY = state.y - prevState.y;

    // Tombol mouse (jika kamu ingin juga mendeteksi delta button bisa ditambahkan di sini)
}

const MouseState& MouseInputDevice::getState() const {
    return state;
}

const MouseDeltaState& MouseInputDevice::getDelta() const {
    return delta;
}

bool MouseInputDevice::isMouseDown(MouseButton button) const {
    return getButtonState(state, button) && !getButtonState(prevState, button);
}

bool MouseInputDevice::isMouseUp(MouseButton button) const {
    return !getButtonState(state, button) && getButtonState(prevState, button);
}

bool MouseInputDevice::isMouseHeld(MouseButton button) const {
    return getButtonState(state, button);
}

