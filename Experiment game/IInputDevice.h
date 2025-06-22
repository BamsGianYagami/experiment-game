#pragma once

/**
 * @brief Kelas abstrak untuk semua perangkat input.
 *
 * Interface ini merepresentasikan satu instance perangkat input fisik 
 * (misalnya satu keyboard, satu mouse, atau satu gamepad). Backend spesifik 
 * (seperti XInputGamepadBackend, WindowsKeyboardBackend) bertanggung jawab 
 * untuk:
 *   - Mendeteksi hardware input yang tersedia,
 *   - Membuat instance IInputDevice untuk setiap hardware,
 *   - Mendaftarkan instance tersebut ke InputManager.
 *
 * InputManager hanya mengenal dan mengelola kumpulan pointer IInputDevice 
 * dan melakukan polling/update setiap frame. Dengan desain ini:
 *   - Backend bisa diubah tanpa mempengaruhi logika InputManager,
 *   - Backend baru bisa ditambahkan untuk platform baru cukup membuat 
 *     turunan IInputDevice dan me-register-nya,
 *   - InputManager tetap sederhana dan generik.
 */
class IInputDevice {
public:
	virtual ~IInputDevice() {}
	virtual void update() = 0;
};