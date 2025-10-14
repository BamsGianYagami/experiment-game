#pragma once
#include "IRenderer.h"
#include <windows.h>  // untuk HWND
#include "IRenderSurface.h"

#include "DrawCommand.h"
#include "MathTypes.h"

class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    bool init(IRenderSurface* surface) override;
    void beginFrame() override;
	void endFrame() override;
    void shutdown() override;

    void Execute(const DrawCommand& command) override;

private:
    void DrawRect(const Vector2& pos, const Vector2& size, const Color& color);
	void DrawText(const std::string& text, const Vector2& position, float fontSize, const Color& color);
    void Begin2D();
    void End2D();
	void Begin3D() override;
	void End3D() override;
	void BeginOverlay() override;
	void EndOverlay() override;

    HDC hDC;
    HGLRC hGLRC;
};

