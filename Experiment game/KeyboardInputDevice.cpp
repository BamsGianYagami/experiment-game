#pragma once
#include "StdAfx.h"
#include "KeyboardInputDevice.h"

KeyboardInputDevice::KeyboardInputDevice(IKeyboardBackend* backend)
    : backend(backend)
{}

KeyboardInputDevice::~KeyboardInputDevice() {}

void KeyboardInputDevice::update() {
    previousState = currentState;            // simpan state sebelumnya
    backend->update(currentState);           // isi ulang currentState dari backend
}

const KeyboardState& KeyboardInputDevice::getState() const {
    return currentState;
}

bool KeyboardInputDevice::isKeyDown(KeyCode code) const {
    return !previousState.isKeyPressed(code) && currentState.isKeyPressed(code);
}

bool KeyboardInputDevice::isKeyUp(KeyCode code) const {
    return previousState.isKeyPressed(code) && !currentState.isKeyPressed(code);
}

bool KeyboardInputDevice::isKeyHeld(KeyCode code) const {
    return currentState.isKeyPressed(code);
}
