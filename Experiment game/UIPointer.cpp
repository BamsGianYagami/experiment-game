#include "StdAfx.h"
#include "UIPointer.h"
#include "UIPointer.h"
#include <cmath> // for std::abs or length calculation

const float DRAG_THRESHOLD = 5.0f;     // jarak piksel untuk mulai drag
const float HOLD_THRESHOLD = 0.5f;     // waktu detik untuk dianggap hold
const float CLICK_MAX_TIME = 0.3f;     // max waktu untuk click

UIPointer::UIPointer(int id)
    : id(id), heldDuration(0.0f), wasDown(false), isCurrentlyDown(false),
      dragging(false), clicked(false), heldTriggered(false)
{
    position = Vector2(0, 0);
    prevPosition = Vector2(0, 0);
    dragStart = Vector2(0, 0);
}

void UIPointer::updateState(const Vector2& newPos, bool isDown, float deltaTime)
{
    prevPosition = position;
    position = newPos;

    wasDown = isCurrentlyDown;
    isCurrentlyDown = isDown;

    // update held time
    if (isCurrentlyDown) {
        heldDuration += deltaTime;

        // drag detection
        if (!dragging) {
            if ((position - dragStart).length() >= DRAG_THRESHOLD) {
                dragging = true;
            }
        }

        // set drag start pos if new down
        if (!wasDown) {
            dragStart = position;
            heldDuration = 0.0f;
            heldTriggered = false;
        }

    } else {
        // button released
        if (wasDown) {
            // click detection
            if (!dragging && heldDuration <= CLICK_MAX_TIME) {
                clicked = true;
            }
        }

        heldDuration = 0.0f;
        dragging = false;
        heldTriggered = false;
    }

    // hold gesture (delay trigger)
    if (isCurrentlyDown && !heldTriggered && heldDuration >= HOLD_THRESHOLD) {
        heldTriggered = true;
    }
}

void UIPointer::resetFrameState()
{
    clicked = false;
    // you may reset other per-frame flags here
}

int UIPointer::getId() const {
    return id;
}

Vector2 UIPointer::getPosition() const {
    return position;
}

Vector2 UIPointer::getDelta() const {
    return position - prevPosition;
}

bool UIPointer::isDown() const {
    return isCurrentlyDown && !wasDown;
}

bool UIPointer::isHeld() const {
    return isCurrentlyDown;
}

bool UIPointer::isUp() const {
    return !isCurrentlyDown && wasDown;
}

bool UIPointer::isDragging() const {
    return dragging;
}

bool UIPointer::isClick() const {
    return clicked;
}

bool UIPointer::isHold() const {
    return heldTriggered;
}
