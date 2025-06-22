#include "StdAfx.h"
#include "UIPointerManager.h"
// #include "MouseInputDevice.h"
// #include "MouseButton.h"

// UIPointerManager::UIPointerManager() {
//     // Buat 1 pointer default untuk mouse (ID 0)
//     activePointers.emplace_back(0);
// }

// void UIPointerManager::update(float deltaTime, const std::vector<IInputDevice*>& devices) {
// 	for (std::vector<IInputDevice*>::const_iterator it = devices.begin(); it != devices.end(); ++it) {
// 		// Cek apakah device ini adalah mouse
// 		if (MouseInputDevice* mouse = dynamic_cast<MouseInputDevice*>(*it)) {
// 			// proses mouse
// 			const MouseState& state = mouse->getState();
    
// 			// Pointer ID 0 = mouse
// 			UIPointer& pointer = activePointers[0];

// 			Vector2 mousePos(state.x, state.y);
// 			bool isDown = mouse->isMouseHeld(GE::MouseButton_Left);

// 			pointer.updateState(mousePos, isDown, deltaTime);
// 		}
// 	}
// }

// void UIPointerManager::resetAll() {
// 	for (std::vector<UIPointer>::iterator it = activePointers.begin(); it != activePointers.end(); ++it) {
//         it->resetFrameState();
//     }
// }

// int UIPointerManager::getPointerCount() const {
//     return static_cast<int>(activePointers.size());
// }

// const UIPointer& UIPointerManager::getPointer(int index) const {
//     return activePointers[index];
// }

UIPointerManager::UIPointerManager(){}
UIPointerManager::~UIPointerManager(){}