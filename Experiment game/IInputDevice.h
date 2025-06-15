#pragma once

class IInputDevice {
public:
	virtual ~IInputDevice() {}
    virtual void update() = 0;
};
