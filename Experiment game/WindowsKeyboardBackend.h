#pragma once

#include "IKeyboardBackend.h"
#include <Windows.h>

/**
 * @brief Implementasi backend keyboard untuk platform Windows.
 * 
 * Menggunakan fungsi WinAPI seperti GetAsyncKeyState untuk membaca status tombol.
 * Mengisi KeyboardState yang disediakan oleh KeyboardInputDevice.
 */
class WindowsKeyboardBackend : public IKeyboardBackend {
public:
    WindowsKeyboardBackend();
    ~WindowsKeyboardBackend();

    /**
     * @brief Update status semua tombol dan mengisi objek KeyboardState.
     * 
     * @param state Objek KeyboardState yang akan diperbarui.
     */
    void update(KeyboardState& state) override;
	
	// Called from the window message handler
    void onKeyDown(WPARAM wParam);
    void onKeyUp(WPARAM wParam);

private:
	bool keyStates[256];
};