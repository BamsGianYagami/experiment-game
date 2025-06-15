#pragma once

#include "IAudio.h"
#include <map>
#include <string>
#include <al.h>
#include <alc.h>

/**
 * @class OpenALAudio
 * @brief Implementasi subsistem audio menggunakan OpenAL untuk Windows dan Android.
 *
 * Kelas ini menyediakan implementasi dari interface IAudio yang memanfaatkan OpenAL sebagai backend.
 * Dapat memutar audio 2D maupun 3D, termasuk pengaturan posisi listener dan sumber suara.
 */
class OpenALAudio : public IAudio {
public:
	 /**
     * @brief Konstruktor default.
     */
    OpenALAudio();
	/**
     * @brief Destruktor. Akan memanggil shutdown() jika belum dipanggil secara manual.
     */
    ~OpenALAudio();

	/**
     * @brief Inisialisasi perangkat dan context OpenAL.
     * @return true jika berhasil, false jika gagal membuka device atau membuat context.
     */
    bool init() override;

	/**
     * @brief Membersihkan semua buffer, source, context, dan menutup device OpenAL.
     */
    void shutdown() override;

	/**
     * @brief Memuat file suara ke dalam buffer dan membuat source OpenAL.
     * @param id ID string unik untuk mengakses suara.
     * @param filepath Lokasi file suara di disk (format .wav disarankan).
     * @return true jika sukses, false jika gagal memuat file.
     */
    bool loadSound(const std::string& id, const std::string& filepath) override;

	 /**
     * @brief Memutar suara berdasarkan ID.
     * @param id ID suara yang sudah dimuat.
     * @param loop Jika true, suara akan berulang.
     */
    void playSound(const std::string& id, bool loop = false) override;

	/**
     * @brief Menghentikan suara yang sedang dimainkan.
     * @param id ID suara yang dimaksud.
     */
    void stopSound(const std::string& id) override;

	/**
     * @brief Mengatur volume suara tertentu.
     * @param id ID suara.
     * @param volume Nilai antara 0.0 (diam) hingga 1.0 (penuh).
     */
    void setVolume(const std::string& id, float volume) override;

	/**
     * @brief Update berkala untuk keperluan suara dinamis atau streaming.
     */
    void update() override;

	/**
     * @brief Mengatur posisi listener (biasanya mengikuti posisi kamera/pemain).
     * @param x Posisi X.
     * @param y Posisi Y.
     * @param z Posisi Z.
     */
    void setListenerPosition(float x, float y, float z) override;

	/**
     * @brief Mengatur arah pandang listener.
     * @param fx, fy, fz Vector "forward" arah pandang.
     * @param ux, uy, uz Vector "up" dari kepala listener.
     */
    void setListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz) override;

	/**
     * @brief Memainkan suara 3D pada posisi tertentu. Misalnya untuk memutar suara ledakan di lokasi tertentu
     * @param id ID suara.
     * @param x, y, z Posisi sumber suara di ruang 3D.
     */
    void playSound3D(const std::string& id, float x, float y, float z) override;

	/**
     * @brief (Opsional) Mengatur preset ruangan, misal efek echo/reverb.
     * @param presetName Nama preset (placeholder).
     */
    void setRoomPreset(const std::string& presetName) override;

	/**
     * @brief Mengatur ulang posisi sumber suara setelah diputar. Jika suara yang sudah diputar dan perlu dipindahkan
     * @param id ID suara.
     * @param x, y, z Posisi baru suara di dunia 3D.
     */
    void setSoundPosition(const std::string& id, float x, float y, float z) override;

private:
    ALCdevice* device;				            //< Perangkat audio aktif.
    ALCcontext* context;						//< Context OpenAL yang sedang digunakan.
    std::map<std::string, SoundHandle> sounds;	//< Peta dari ID ke sumber dan buffer suara.

    // Utility function
    bool OpenALAudio::loadWAV(const std::string& filepath, ALuint& outBuffer);
};
