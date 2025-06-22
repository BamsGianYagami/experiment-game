#pragma once

#include "MathTypes.h" // vector 2D class kamu

class UIPointer {
public:
    UIPointer(int id);

    void updateState(const Vector2& newPos, bool isDown, float deltaTime);

    // === Aksesor umum ===
    int getId() const;
    Vector2 getPosition() const;
    Vector2 getDelta() const;

    bool isDown() const;
    bool isHeld() const;
    bool isUp() const;

    bool isDragging() const;
    bool isClick() const;
    bool isHold() const;

    // === Event reset ===
    void resetFrameState();

private:
    int id;
    Vector2 position;
    Vector2 prevPosition;
    Vector2 dragStart;
    float heldDuration;

    bool wasDown;
    bool isCurrentlyDown;

    bool dragging;
    bool clicked;
    bool heldTriggered;
};

/* Catatan
Bisa disederhanakan jika kamu hanya butuh gesture dasar.

Bisa dikembangkan dengan UIPointerType enum (mouse, touch, gamepad).

Bisa ditambahkan swipeDirection, doubleTapDetected, dll nanti.*/