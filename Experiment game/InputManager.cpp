#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager() {
    std::cout << "InputHandler created\n";
}

InputManager::~InputManager() {
    std::cout << "InputHandler destroyed\n";
}

void InputManager::registerDevice(IInputDevice* device) {
    devices.push_back(device);

    // Coba cast ke masing-masing tipe input
    if (KeyboardInputDevice* kbd = dynamic_cast<KeyboardInputDevice*>(device)) {
        keyboard = kbd;
    }
	else if (MouseInputDevice* ms = dynamic_cast<MouseInputDevice*>(device)) {
        mouse = ms;
    }
//	else if (GamepadInputDevice* gp = dynamic_cast<GamepadInputDevice*>(device)) {
//        gamepad = gp;
//    }
}

KeyboardInputDevice* InputManager::getKeyboard() {
    return keyboard; // <- ini contoh implementasi
}

MouseInputDevice* InputManager::getMouse() {
    return mouse;
}

void InputManager::updateAllDevices() {
    for (std::vector<IInputDevice*>::iterator it = devices.begin(); it != devices.end(); ++it) {
        (*it)->update();
    }
}