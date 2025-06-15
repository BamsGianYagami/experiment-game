#pragma once
#include "IInputDevice.h"
#include "KeyboardState.h"
#include "IKeyboardBackend.h"
#include "KeyCode.h"

class KeyboardInputDevice : public IInputDevice {
public:
    explicit KeyboardInputDevice(IKeyboardBackend* backend);
    ~KeyboardInputDevice();

    void update() override;
    const KeyboardState& getState() const;

    // Delta State Queries
    bool isKeyDown(KeyCode code) const;
    bool isKeyUp(KeyCode code) const;
    bool isKeyHeld(KeyCode code) const;

private:
    KeyboardState previousState;
    KeyboardState currentState;
    IKeyboardBackend* backend;
};
