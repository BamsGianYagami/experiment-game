#pragma once
#include "IWindow.h"

class WindowManagerWin32 : public IWindow {
public:
    WindowManagerWin32();
    ~WindowManagerWin32();

    bool create(int width, int height, const wchar_t* title) override;
    void processEvents() override;
    bool shouldClose() const override;
    NativeWindowHandle getNativeHandle() const override;

private:
    HWND hWnd;
    bool running;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
