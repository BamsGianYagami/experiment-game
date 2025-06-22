#pragma once
#include "stdafx.h"
#include "IInputDevice.h"
#include "KeyboardInputDevice.h"
#include "MouseInputDevice.h"
#include <vector>

/**
 * @brief InputManager bertugas sebagai pengelola perangkat input.
 *
 * InputManager:
 *   - Menyimpan daftar perangkat input (IInputDevice*) untuk di-update,
 *   - Menyediakan metode untuk mengambil perangkat spesifik berdasarkan tipe,
 *   - Tidak tahu detail cara perangkat dideteksi maupun dibuat,
 *     melainkan hanya menerima pendaftaran perangkat dari Backend.
 *
 * Dengan begitu, InputManager terpisah dari logika low-level device detection.
 */
using namespace GE;
class InputManager {
public:
    InputManager();
    ~InputManager();

    void registerDevice(IInputDevice* device);
    void updateAllDevices();

	template<typename T> T* getDevice();

private:
    std::vector<IInputDevice*> devices;
};
