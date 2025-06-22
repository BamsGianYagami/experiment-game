#pragma once
#include "MathTypes.h"

struct NativeWindowHandle {
    enum Type { Win32, Android };
    Type type;
    void* handle;
};

class IWindow {
public:
    virtual bool create(const Vector2& resolution, const wchar_t* title) = 0;
    virtual void processEvents() = 0;
    virtual bool shouldClose() const = 0;
    virtual NativeWindowHandle getNativeHandle() const = 0;
    virtual ~IWindow() {}
	virtual const Vector2* getWindowResolution() const { return resolution; }

protected:
	const Vector2* resolution;
};
