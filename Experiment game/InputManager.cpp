#include "stdafx.h"
#include "InputManager.h"
#include <typeinfo>   // untuk typeid


InputManager::InputManager() {
    std::cout << "InputHandler created\n";
}

InputManager::~InputManager() {
    std::cout << "InputHandler destroyed\n";
}

void InputManager::registerDevice(IInputDevice* device) {
    devices.push_back(device);
}

template<typename T> T* InputManager::getDevice(){
	for (std::vector<IInputDevice*>::iterator it = devices.begin(); it != devices.end(); ++it) {
		if (T* typedDevice = dynamic_cast<T*>(*it)) {
            //std::cout << "Found device of type: " << typeid(*typedDevice).name() << "\n";
            return typedDevice;
        }
    }
    std::cout << "No device of type: " << typeid(T).name() << " found.\n";
    return nullptr;
}



void InputManager::updateAllDevices() {
    for (std::vector<IInputDevice*>::iterator it = devices.begin(); it != devices.end(); ++it) {
		IInputDevice* device = *it;
        //std::cout << "Updating device of type: " << typeid(*device).name() << "\n";
        device->update();
    }
}

void InputManager::CallBackInput(const InputEvent& e) {
    /*std::cout << "[CALLBACK] CallBackInput" << std::endl;
    std::cout << "Address of InputEvent: " << &e << std::endl;

    std::cout << "type: " << e.type
              << ", keyOrButton: " << e.keyOrButton
              << ", mouseButton: " << e.mouseButton
              << ", x: " << e.x
              << ", y: " << e.y
              << ", scrollDelta: " << e.scrollDelta << std::endl;*/
}
