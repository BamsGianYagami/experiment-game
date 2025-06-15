#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <GL/gl.h>
#include <iostream>

OpenGLRenderer::OpenGLRenderer() : hDC(NULL), hGLRC(NULL) {
	std::cout << "OpenGLRenderer created\n";
}

OpenGLRenderer::~OpenGLRenderer() {
    shutdown();
	std::cout << "OpenGLRenderer destroyed\n";
}

bool OpenGLRenderer::init(IWindow* window) {
    NativeWindowHandle handle = window->getNativeHandle();

    if (handle.type != NativeWindowHandle::Win32) {
        std::cerr << "Unsupported platform for OpenGLRenderer.\n";
        return false;
    }

    HWND hwnd = reinterpret_cast<HWND>(handle.handle);
    hDC = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0) return false;

    if (!SetPixelFormat(hDC, pixelFormat, &pfd)) return false;

    hGLRC = wglCreateContext(hDC);
    if (!hGLRC) return false;

    if (!wglMakeCurrent(hDC, hGLRC)) return false;

    return true;
}

void OpenGLRenderer::render() {
	//std::cout << "[OpenGLRenderer] Rendering frame...\n";
    // Clear the buffer color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    SwapBuffers(hDC);
}

void OpenGLRenderer::shutdown() {
    if (hGLRC) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hGLRC);
        hGLRC = NULL;
    }

    if (hDC) {
        ReleaseDC(WindowFromDC(hDC), hDC);
        hDC = NULL;
    }
}