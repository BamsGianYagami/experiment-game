#pragma once
#include "IMouseBackend.h"
#include "MouseState.h"
#include <Windows.h>

class WindowsMouseBackend : public IMouseBackend {
public:
	WindowsMouseBackend();
    ~WindowsMouseBackend();

    void update(MouseState& state) override;
};
