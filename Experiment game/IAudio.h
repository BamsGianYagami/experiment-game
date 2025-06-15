#pragma once
#include <string>


struct SoundHandle {
    unsigned int source;
    unsigned int buffer;
};


class IAudio {
public:
    virtual ~IAudio() {}

    virtual bool init() = 0;
    virtual void shutdown() = 0;

    virtual bool loadSound(const std::string& id, const std::string& filepath) = 0;
    virtual void playSound(const std::string& id, bool loop = false) = 0;
    virtual void stopSound(const std::string& id) = 0;
    virtual void setVolume(const std::string& id, float volume) = 0;

    virtual void update() = 0; // untuk audio streaming / posisi 3D misalnya

	// Posisi listener (kamera / pemain)
	virtual void setListenerPosition(float x, float y, float z) = 0;
	virtual void setListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz) = 0;

	// Mainkan suara di posisi tertentu (bisa jauh, dekat, atau di balik tembok nanti)
	virtual void playSound3D(const std::string& id, float x, float y, float z) = 0;

	// Atur parameter ruang (reverb preset, atau simulasi jenis lingkungan)
	virtual void setRoomPreset(const std::string& presetName) = 0;

	virtual void setSoundPosition(const std::string& id, float x, float y, float z) = 0;
};
