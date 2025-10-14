// Config.h
#pragma once
#include "MathTypes.h"

struct SystemConfig {
    struct Video {
        Vector2 resolution;
        float pixelDensity;
        bool fullscreen;

        Video() 
          : resolution(800, 600),
            pixelDensity(1.0f),
            fullscreen(false) {}
    } video;

    struct Audio {
        float masterVolume;
        float musicVolume;
        float sfxVolume;

        Audio() 
          : masterVolume(1.0f),
            musicVolume(0.8f),
            sfxVolume(0.8f) {}
    } audio;

    struct Input {
        int sensitivity;
        bool invertYAxis;

        Input() 
          : sensitivity(100),
            invertYAxis(false) {}
    } input;

    struct Debug {
        bool showFps;
        bool drawCollisionBoxes;

        Debug() 
          : showFps(true),
            drawCollisionBoxes(false) {}
    } debug;

    // Tidak perlu constructor di Config luar,
    // kecuali mau logika khusus
    SystemConfig() {} 
};