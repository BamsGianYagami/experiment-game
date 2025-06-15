#pragma once

#include <cstdint>
#include <cstring>

/**
 * @brief Struktur yang merepresentasikan status semua tombol keyboard.
 * 
 * KeyboardState dapat menyimpan hingga 256 tombol secara umum, mencakup huruf, angka, F1-F12, panah, dsb.
 * Implementasi backend (seperti WindowsKeyboardBackend atau AndroidKeyboardBackend) akan mengatur mapping key sesuai platform.
 */
struct KeyboardState {
    static const int MAX_KEYS = 256;

    bool keys[MAX_KEYS];

    KeyboardState() {
        std::memset(keys, 0, sizeof(keys));
    }

    /**
     * @brief Mengecek apakah tombol dengan kode tertentu sedang ditekan.
     * 
     * @param keyCode Kode tombol (0-255).
     * @return true jika tombol ditekan, false jika tidak.
     */
    inline bool isKeyPressed(uint8_t keyCode) const {
        return keys[keyCode];
    }

    /**
     * @brief Menandai tombol tertentu sedang ditekan.
     */
    inline void pressKey(uint8_t keyCode) {
        keys[keyCode] = true;
    }

    /**
     * @brief Menandai tombol tertentu dilepas.
     */
    inline void releaseKey(uint8_t keyCode) {
        keys[keyCode] = false;
    }

    /**
     * @brief Reset seluruh tombol ke tidak ditekan.
     */
    inline void clear() {
        std::memset(keys, 0, sizeof(keys));
    }
};
