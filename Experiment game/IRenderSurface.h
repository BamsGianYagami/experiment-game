#pragma once
#include "MathTypes.h"

struct NativeWindowHandle {
    enum Type { Win32, Android };
    Type type;
    void* handle;
};
class IRenderSurface {
public:
	virtual bool createSurface(const Vector2& resolution, const wchar_t *title) = 0;
    virtual NativeWindowHandle getNativeHandle() const = 0;
	virtual const Vector2* getResolution() const { return resolution; }
    virtual ~IRenderSurface() {}

protected:
	const Vector2* resolution;
};