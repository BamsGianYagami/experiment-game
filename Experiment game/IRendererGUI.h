#pragma once
#include <cstdint>


/**
 * @interface IRendererGUI
 * @brief Interface abstrak untuk sistem rendering GUI.
 *
 * IRendererGUI bertanggung jawab menggambar elemen-elemen GUI seperti
 * rectangle, teks, dan gambar ke layar menggunakan backend rendering yang tersedia
 * (OpenGL, Vulkan, DirectX, dll).
 *
 * Interface ini memungkinkan pemisahan antara logika GUI dan implementasi rendering,
 * mendukung arsitektur modular serta memungkinkan GUI dipakai ulang di berbagai platform.
 *
 * @see IWidget, IGUI
 */

class IRendererGUI {
public:
	virtual ~IRendererGUI() {};

    // Dipanggil saat mulai menggambar frame GUI
    virtual void BeginFrame() = 0;

    // Dipanggil saat selesai menggambar frame GUI
    virtual void EndFrame() = 0;

    // Menggambar rectangle berwarna
    virtual void DrawRect(float x, float y, float width, float height, uint32_t color) = 0;

    // Menggambar rectangle dengan border
    virtual void DrawRectBorder(float x, float y, float width, float height, float thickness, uint32_t color) = 0;

    // Menggambar teks
    virtual void DrawText(const char* text, float x, float y, uint32_t color) = 0;

    // Menggambar gambar (misalnya dari atlas atau ID texture)
    virtual void DrawImage(int textureID, float x, float y, float width, float height) = 0;

    // Scissor/clip region (optional, tergantung renderer)
    virtual void PushClip(float x, float y, float width, float height) = 0;
    virtual void PopClip() = 0;

    // Untuk transformasi 2D jika diperlukan
    virtual void PushTransform(float dx, float dy) = 0;
    virtual void PopTransform() = 0;
};
