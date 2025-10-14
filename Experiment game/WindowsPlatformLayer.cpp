#include "StdAfx.h"
#include "WindowsPlatformLayer.h"
#include <iostream>
#include "windowsx.h"
#include "MouseButton.h"

WindowsPlatformLayer::WindowsPlatformLayer() {}
WindowsPlatformLayer::~WindowsPlatformLayer() {}

bool WindowsPlatformLayer::createSurface(const Vector2& resolution, const wchar_t* title) {
	this->resolution = &resolution;

	int width = static_cast<int>(resolution.x);
	int height = static_cast<int>(resolution.y);
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const wchar_t* className = L"MyEngineWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, className, title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance, this // pass `this` to WM_NCCREATE
    );

    if (!hwnd) return false;
    return true;
}

void WindowsPlatformLayer::processPlatformEvents() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

NativeWindowHandle WindowsPlatformLayer::getNativeHandle() const {
    NativeWindowHandle handle;
    handle.type = NativeWindowHandle::Win32;
    handle.handle = reinterpret_cast<void*>(hwnd);
    return handle;
}

// Static WindowProc
LRESULT CALLBACK WindowsPlatformLayer::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    WindowsPlatformLayer* self = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        self = static_cast<WindowsPlatformLayer*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
    } else {
        self = reinterpret_cast<WindowsPlatformLayer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (self && self->inputCallback) {
        switch (msg) {
            case WM_KEYDOWN: {
                InputEvent ev;
                ev.type = GE::InputEventType::KeyDown;
                ev.keyOrButton = (int)wParam;
                self->inputCallback(ev);
                return 0;
            }
            case WM_KEYUP: {
                InputEvent ev;
                ev.type = GE::InputEventType::KeyUp;
                ev.keyOrButton = (int)wParam;
                self->inputCallback(ev);
                return 0;
            }
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			case WM_MOUSEMOVE:
			case WM_MOUSEWHEEL: {
				GE::InputEvent ev;
				ev.x = GET_X_LPARAM(lParam);
				ev.y = GET_Y_LPARAM(lParam);

				switch (msg) {
					case WM_LBUTTONDOWN:
						ev.type = GE::InputEventType::MouseButtonDown;
						ev.mouseButton = MouseButton::MouseButton_Left;
						break;
					case WM_LBUTTONUP:
						ev.type = GE::InputEventType::MouseButtonUp;
						ev.mouseButton = MouseButton::MouseButton_Left;
						break;
					case WM_RBUTTONDOWN:
						ev.type = GE::InputEventType::MouseButtonDown;
						ev.mouseButton = MouseButton::MouseButton_Right;
						break;
					case WM_RBUTTONUP:
						ev.type = GE::InputEventType::MouseButtonUp;
						ev.mouseButton = MouseButton::MouseButton_Right;
						break;
					case WM_MBUTTONDOWN:
						ev.type = GE::InputEventType::MouseButtonDown;
						ev.mouseButton = MouseButton::MouseButton_Middle;
						break;
					case WM_MBUTTONUP:
						ev.type = GE::InputEventType::MouseButtonUp;
						ev.mouseButton = MouseButton::MouseButton_Middle;
						break;
					case WM_XBUTTONDOWN:
						ev.type = GE::InputEventType::MouseButtonDown;
						ev.mouseButton = (HIWORD(wParam) == XBUTTON1) ? MouseButton::MouseButton_Mouse4 : MouseButton::MouseButton_Mouse5;
						break;
					case WM_XBUTTONUP:
						ev.type = GE::InputEventType::MouseButtonUp;
						ev.mouseButton = (HIWORD(wParam) == XBUTTON1) ? MouseButton::MouseButton_Mouse4 : MouseButton::MouseButton_Mouse5;
						break;
					case WM_MOUSEMOVE:
						ev.type = GE::InputEventType::MouseMove;
						break;
					case WM_MOUSEWHEEL:
						ev.type = InputEventType::MouseWheel;
						ev.scrollDelta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
						break;
				}

				self->inputCallback(ev);
				return 0;
			}

        }
    }

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}