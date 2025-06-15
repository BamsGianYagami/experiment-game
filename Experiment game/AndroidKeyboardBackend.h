#pragma once

#ifdef __ANDROID__  // ⬅️ Hanya dikompilasi saat build Android

#include "IKeyboardBackend.h"
#include "KeyboardState.h"
#include <mutex>

/**
 * @brief Backend keyboard khusus Android.
 *
 * Mengumpulkan event key dari native layer (JNI/NativeActivity) dan menyimpan statusnya.
 * Kelas ini tidak digunakan di platform selain Android.
 */
class AndroidKeyboardBackend : public IKeyboardBackend {
public:
    AndroidKeyboardBackend();
    ~AndroidKeyboardBackend();

    /**
     * @brief Diupdate oleh input device untuk polling key state terbaru.
     */
    void update(KeyboardState& state) override;

    /**
     * @brief Event dari Android saat tombol ditekan.
     */
    void onKeyDown(int androidKeyCode);

    /**
     * @brief Event dari Android saat tombol dilepas.
     */
    void onKeyUp(int androidKeyCode);

private:
    KeyboardState bufferState;
    std::mutex stateMutex;

    KeyCode mapAndroidKeyCode(int androidKeyCode);  // mapping dari Android ke enum universal
};

#endif  // __ANDROID__
