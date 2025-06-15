#pragma once
#include "IRenderer.h"
#include <windows.h>  // untuk HWND
#include "IWindow.h"  // untuk IWindow

class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    bool init(IWindow* windowHandle) override;
    void render() override;
    void shutdown() override;

private:
    HDC hDC;
    HGLRC hGLRC;
};
