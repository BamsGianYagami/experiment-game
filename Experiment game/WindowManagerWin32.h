#pragma once
#include "IWindow.h"
#include "WindowsKeyboardBackend.h"

class WindowManagerWin32 : public IWindow {
public:
    WindowManagerWin32();
    ~WindowManagerWin32();

    bool create(const Vector2& resolution, const wchar_t* title) override;
    void processEvents() override;
    bool shouldClose() const override;
    NativeWindowHandle getNativeHandle() const override;

	void setKeyboardBackend(WindowsKeyboardBackend* kb) { keyboardBackend = kb; }


private:
    HWND hWnd;
    bool running;
	WindowsKeyboardBackend *keyboardBackend; //backend keyboard di windows butuh callback dari window

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
