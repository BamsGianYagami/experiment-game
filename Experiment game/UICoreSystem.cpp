#include "StdAfx.h"
#include "UICoreSystem.h"
// #include "InputManager.h"
// #include "IRendererGUI.h"

// UICoreSystem::UICoreSystem() {
//     // Inisialisasi jika diperlukan
// }

// UICoreSystem::~UICoreSystem() {
//     // Cleanup jika perlu
// }

// void UICoreSystem::update(InputManager* input) {
//     // 1. Update semua pointer (mouse/touch/gamepad) dan gesture
//     pointerManager.update(0.0f, input); //belum ada delta time disini!

//     // 2. Evaluasi interaksi (hover, click, drag, dll)
//     eventDispatcher.dispatch(pointerManager);

//     // 3. Update fokus atau panel yang sedang di-drag
//     focusManager.update(pointerManager);

//     // 4. (opsional) Layouting otomatis jika layoutEngine dipakai
//     // layoutEngine.recalculateLayout();
// }

// void UICoreSystem::render(IRendererGUI* renderer) {
//     // Gambar seluruh elemen UI
//     drawSystem.draw(renderer);
// }

// void UICoreSystem::reset() {
//     pointerManager.resetAll();
//     focusManager.reset();
//     // Bisa reset dispatcher jika menyimpan state
// }

UICoreSystem::UICoreSystem() {}
UICoreSystem::~UICoreSystem() {}