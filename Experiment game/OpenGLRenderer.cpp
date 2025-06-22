#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <GL/gl.h>
#include <iostream>

using namespace GE;

OpenGLRenderer::OpenGLRenderer() : hDC(NULL), hGLRC(NULL) {
	std::cout << "OpenGLRenderer created\n";
}

OpenGLRenderer::~OpenGLRenderer() {
    shutdown();
	std::cout << "OpenGLRenderer destroyed\n";
}

bool OpenGLRenderer::init(IWindow* window) {
    NativeWindowHandle handle = window->getNativeHandle();
	this->resolution = window->getWindowResolution();

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

    std::cout << "OpenGL context initialized successfully.\n";

    return true;
}

void OpenGLRenderer::beginFrame(){
	// Clear with black, could be configurable later
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::endFrame() {
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

// ---------- Tambahan baru untuk DrawCommand support ----------

void OpenGLRenderer::Execute(const DrawCommand& command) {
    switch (command.type) {
		case DrawCommand_Rect:
            DrawRect(command.position, command.size, command.color);
            break;
		
		case DrawCommand_Text:
            DrawText(command.text, command.position, command.fontSize, command.color);
            break;

        default:
            break;
    }
}

void OpenGLRenderer::DrawRect(const Vector2& pos, const Vector2& size, const Color& color) {
    glDisable(GL_TEXTURE_2D); // Untuk solid color
    glColor4f(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
    glVertex2f(pos.x,         pos.y);
    glVertex2f(pos.x + size.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glVertex2f(pos.x,         pos.y + size.y);
    glEnd();
}

void OpenGLRenderer::DrawText(const std::string& text, const Vector2& position, float fontSize, const Color& color) {
    if (!hDC) return;

    // Pilih font dari GDI
    HFONT hFont = CreateFontA(
        static_cast<int>(fontSize), 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
        "Arial"
    );

    HFONT oldFont = (HFONT)SelectObject(hDC, hFont);

    // Buat display list untuk 256 karakter ASCII
    const GLuint base = 1000;
    wglUseFontBitmapsA(hDC, 0, 256, base);

    glColor4f(color.r, color.g, color.b, color.a);

    // Pindah ke posisi (ingat: posisi di OpenGL window space)
    glRasterPos2f(position.x, position.y);

    glListBase(base);
    glCallLists(static_cast<GLsizei>(text.length()), GL_UNSIGNED_BYTE, text.c_str());

    // Cleanup
    SelectObject(hDC, oldFont);
    DeleteObject(hFont);
}

void OpenGLRenderer::Begin2D() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	int horizontal = static_cast<float>(resolution->x);
	int vertical = static_cast<float>(resolution->y);
    glOrtho(0, horizontal, vertical, 0, -1, 1); // Origin kiri atas

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	glDisable(GL_DEPTH_TEST); // GUI doesn't need depth
}

void OpenGLRenderer::End2D() {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void OpenGLRenderer::Begin3D() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

	//TODO: ini 4x4 matrix, tadinya pakai untuk untuk menghindari gluPerspective tapi nanti harusnya bikin library sendiri
    float fov = 60.0f;
	float aspect = resolution->x / resolution->y;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    float f = 1.0f / tanf(fov * 0.5f * 3.14159265f / 180.0f);

    float proj[16] = {
        f / aspect, 0,  0,                                 0,
        0,          f,  0,                                 0,
        0,          0,  (farPlane + nearPlane) / (nearPlane - farPlane), -1,
        0,          0,  (2 * farPlane * nearPlane) / (nearPlane - farPlane), 0
    };

    glLoadMatrixf(proj);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


void OpenGLRenderer::End3D() {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void OpenGLRenderer::BeginOverlay() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Gunakan projection 3D yang sama seperti Begin3D
    float fov = 60.0f;
    float aspect = resolution->x / resolution->y;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    float f = 1.0f / tanf(fov * 0.5f * 3.14159265f / 180.0f);

    float proj[16] = {
        f / aspect, 0,  0,                                 0,
        0,          f,  0,                                 0,
        0,          0,  (farPlane + nearPlane) / (nearPlane - farPlane), -1,
        0,          0,  (2 * farPlane * nearPlane) / (nearPlane - farPlane), 0
    };

    glLoadMatrixf(proj);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Set depth state untuk overlay
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);    // Selalu lolos depth test
    glDepthMask(GL_FALSE);     // Jangan tulis ke depth buffer
}

void OpenGLRenderer::EndOverlay() {
	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glDepthFunc(GL_LESS);             // Kembalikan depth state
    glDepthMask(GL_TRUE);
}