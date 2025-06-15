#pragma once

/**
 * @brief Struktur yang menyimpan status mouse saat ini.
 */
struct MouseState {
    int x;
    int y;

    bool leftButton;
    bool rightButton;
    bool middleButton;
    bool mouse4Button;
    bool mouse5Button;

    int scrollDelta;

    MouseState()
        : x(0), y(0),
          leftButton(false), rightButton(false), middleButton(false),
          mouse4Button(false), mouse5Button(false),
          scrollDelta(0) {}

    bool operator==(const MouseState& other) const {
        return x == other.x && y == other.y &&
            leftButton == other.leftButton &&
            rightButton == other.rightButton &&
            middleButton == other.middleButton &&
            mouse4Button == other.mouse4Button &&
            mouse5Button == other.mouse5Button &&
            scrollDelta == other.scrollDelta;
    }

    bool operator!=(const MouseState& other) const {
        return !(*this == other);
    }
};
