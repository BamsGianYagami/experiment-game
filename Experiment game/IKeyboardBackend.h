#pragma once
#include "KeyboardState.h"

class IKeyboardBackend {
public:
    virtual ~IKeyboardBackend() {}
    virtual void update(KeyboardState& state) = 0;
};
