#pragma once
#include "KeyboardState.h"

/**
 * @brief Backend spesifik platform untuk keyboard di Windows.
 *
 * Backend ini:
 *   - Mengecek semua key di Windows menggunakan GetAsyncKeyState(),
 *   - Membuat instance KeyboardInputDevice,
 *   - Mendaftarkannya ke InputManager.
 *
 * Backend ini hanya menangani komunikasi langsung ke API platform.
 * Backend **tidak** bertugas memproses logika game — semua data 
 * dioper ke InputManager untuk diteruskan ke subsistem game.
 */
class IKeyboardBackend {
public:
    virtual ~IKeyboardBackend() {}
    virtual void update(KeyboardState& state) = 0;
};
