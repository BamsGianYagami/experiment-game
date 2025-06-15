#include "StdAfx.h" // jika kamu pakai precompiled header
#include "OpenALAudio.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdint>

#define _CRT_SECURE_NO_WARNINGS

// Constructor
OpenALAudio::OpenALAudio()
    : device(NULL), context(NULL) {
}

// Destructor
OpenALAudio::~OpenALAudio() {
    shutdown();
}

bool OpenALAudio::init() {
    device = alcOpenDevice(NULL);
    if (!device) {
        std::cerr << "Failed to open OpenAL device.\n";
        return false;
    }

    context = alcCreateContext(device, NULL);
    if (!context || !alcMakeContextCurrent(context)) {
        std::cerr << "Failed to create or make current OpenAL context.\n";
        return false;
    }

    std::cout << "OpenAL initialized.\n";
    return true;
}

void OpenALAudio::shutdown() {
    for (std::map<std::string, SoundHandle>::iterator it = sounds.begin(); it != sounds.end(); ++it) {
        alDeleteSources(1, &it->second.source);
        alDeleteBuffers(1, &it->second.buffer);
    }

    if (context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
    }

    if (device) {
        alcCloseDevice(device);
    }

    std::cout << "OpenAL shutdown.\n";
}

bool OpenALAudio::loadSound(const std::string& id, const std::string& filepath) {
    ALuint buffer;
    if (!loadWAV(filepath, buffer)) {
        return false;
    }

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    SoundHandle handle;
    handle.buffer = buffer;
    handle.source = source;

    sounds[id] = handle;
    return true;
}


void OpenALAudio::playSound(const std::string& id, bool loop) {
    if (sounds.find(id) != sounds.end()) {
        alSourcei(sounds[id].source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
        alSourcePlay(sounds[id].source);
    }
}

void OpenALAudio::stopSound(const std::string& id) {
    if (sounds.find(id) != sounds.end()) {
        alSourceStop(sounds[id].source);
    }
}

void OpenALAudio::setVolume(const std::string& id, float volume) {
    if (sounds.find(id) != sounds.end()) {
        alSourcef(sounds[id].source, AL_GAIN, volume);
    }
}

void OpenALAudio::update() {
    // Belum ada audio streaming, jadi tidak ada update khusus
}

void OpenALAudio::setListenerPosition(float x, float y, float z) {
    alListener3f(AL_POSITION, x, y, z);
}

void OpenALAudio::setListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz) {
    float ori[] = { fx, fy, fz, ux, uy, uz };
    alListenerfv(AL_ORIENTATION, ori);
}

void OpenALAudio::playSound3D(const std::string& id, float x, float y, float z) {
    if (sounds.find(id) != sounds.end()) {
        alSource3f(sounds[id].source, AL_POSITION, x, y, z);
        alSourcePlay(sounds[id].source);
    }
}

void OpenALAudio::setSoundPosition(const std::string& id, float x, float y, float z) {
    if (sounds.find(id) != sounds.end()) {
        alSource3f(sounds[id].source, AL_POSITION, x, y, z);
    }
}

void OpenALAudio::setRoomPreset(const std::string& presetName) {
    // Untuk saat ini, kita tidak memakai EFX/OpenAL Soft extensions
    std::cout << "Room preset '" << presetName << "' not implemented.\n";
}

bool OpenALAudio::loadWAV(const std::string& filepath, ALuint& outBuffer) {
    FILE* file = fopen(filepath.c_str(), "rb");
    if (!file) {
        std::cerr << "Gagal membuka file WAV: " << filepath << std::endl;
        return false;
    }

    char chunkId[4];
    uint32_t chunkSize;
    char waveFormat[4];

    fread(chunkId, sizeof(char), 4, file);
    fread(&chunkSize, sizeof(uint32_t), 1, file);
    fread(waveFormat, sizeof(char), 4, file);

    if (strncmp(chunkId, "RIFF", 4) != 0 || strncmp(waveFormat, "WAVE", 4) != 0) {
        std::cerr << "File WAV tidak valid: " << filepath << std::endl;
        fclose(file);
        return false;
    }

    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;

    fread(subchunk1Id, sizeof(char), 4, file);
    fread(&subchunk1Size, sizeof(uint32_t), 1, file);
    fread(&audioFormat, sizeof(uint16_t), 1, file);
    fread(&numChannels, sizeof(uint16_t), 1, file);
    fread(&sampleRate, sizeof(uint32_t), 1, file);
    fread(&byteRate, sizeof(uint32_t), 1, file);
    fread(&blockAlign, sizeof(uint16_t), 1, file);
    fread(&bitsPerSample, sizeof(uint16_t), 1, file);

    // Skip any extra params if subchunk1Size > 16
    if (subchunk1Size > 16) {
        fseek(file, subchunk1Size - 16, SEEK_CUR);
    }

    // Cari subchunk "data"
    char subchunk2Id[4];
    uint32_t subchunk2Size;
    while (true) {
        if (fread(subchunk2Id, sizeof(char), 4, file) != 4) {
            std::cerr << "Tidak menemukan data chunk pada file WAV: " << filepath << std::endl;
            fclose(file);
            return false;
        }
        fread(&subchunk2Size, sizeof(uint32_t), 1, file);
        if (strncmp(subchunk2Id, "data", 4) == 0) {
            break;
        }
        fseek(file, subchunk2Size, SEEK_CUR); // Lewati chunk lain
    }

    unsigned char* data = new unsigned char[subchunk2Size];
    fread(data, sizeof(unsigned char), subchunk2Size, file);
    fclose(file);

    ALenum format;
    if (bitsPerSample == 8) {
        format = (numChannels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
    } else if (bitsPerSample == 16) {
        format = (numChannels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    } else {
        std::cerr << "Format WAV tidak didukung: " << bitsPerSample << " bit\n";
        delete[] data;
        return false;
    }

    alGenBuffers(1, &outBuffer);
    alBufferData(outBuffer, format, data, subchunk2Size, sampleRate);

    delete[] data;
    return true;
}