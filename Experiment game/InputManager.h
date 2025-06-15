#pragma once
#include "stdafx.h"
#include "IInputDevice.h"
#include "KeyboardInputDevice.h"
#include "MouseInputDevice.h"
#include <vector>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void registerDevice(IInputDevice* device);
    void updateAllDevices();

    KeyboardInputDevice* getKeyboard();
    MouseInputDevice* getMouse();
//    GamepadInputDevice* getGamepad();

private:
    std::vector<IInputDevice*> devices;
    KeyboardInputDevice* keyboard;
    MouseInputDevice* mouse;
//    GamepadInputDevice* gamepad;
};
