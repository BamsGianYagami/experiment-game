#include "stdafx.h"
#include "WindowManagerWin32.h"

WindowManagerWin32::WindowManagerWin32() : hWnd(NULL), running(true) {
	keyboardBackend = nullptr;
}

WindowManagerWin32::~WindowManagerWin32() {}

bool WindowManagerWin32::create(const Vector2& resolution, const wchar_t* title) {
	this->resolution = &resolution;

	int width = static_cast<int>(resolution.x);
	int height = static_cast<int>(resolution.y);
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const wchar_t* className = L"MyGameWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    hWnd = CreateWindowEx(
        0,
        className,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance,
		this  // <- pass this to WM_NCCREATE
    );

    if (!hWnd) return false;

    ShowWindow(hWnd, SW_SHOW);
    return true;
}

void WindowManagerWin32::processEvents() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            running = false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool WindowManagerWin32::shouldClose() const {
    return !running;
}

NativeWindowHandle WindowManagerWin32::getNativeHandle() const {
    NativeWindowHandle handle;
	handle.type = NativeWindowHandle::Win32;
	handle.handle = reinterpret_cast<void*>(hWnd);
	return handle;
}

// Static WindowProc callback
LRESULT CALLBACK WindowManagerWin32::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// Ambil this pointer
    WindowManagerWin32* self = nullptr;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        self = static_cast<WindowManagerWin32*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    } else {
        self = reinterpret_cast<WindowManagerWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    // Jika sudah punya self dan keyboardBackend
    if (self && self->keyboardBackend) {
        switch (uMsg) {
        case WM_KEYDOWN:
            self->keyboardBackend->onKeyDown(wParam);
            return 0;
        case WM_KEYUP:
            self->keyboardBackend->onKeyUp(wParam);
            return 0;
        }
    }

	//event default
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
