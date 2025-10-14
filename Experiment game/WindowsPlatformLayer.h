#pragma once
#include <windows.h>
#include <functional>
#include "IPlatformLayer.h"
#include "IRenderSurface.h"
#include "InputEvent.h"

using namespace GE;
// Implementasi platform layer dan render surface sekaligus
class WindowsPlatformLayer : public IPlatformLayer, public IRenderSurface {
public:
    WindowsPlatformLayer();
    virtual ~WindowsPlatformLayer();

    bool createSurface(const Vector2& resolution, const wchar_t* title) override;
    void processPlatformEvents() override;

    NativeWindowHandle getNativeHandle() const override;

    // Dispatch callback untuk event input
    void setInputCallback(std::function<void(const InputEvent&)> callback) {
        inputCallback = callback;
    }

private:
    HWND hwnd;
    std::function<void(const InputEvent&)> inputCallback;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};