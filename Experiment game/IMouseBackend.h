#pragma once
#include "MouseState.h"

class IMouseBackend {
public:
	virtual ~IMouseBackend() {}
    virtual void update(MouseState& state) = 0;
};
