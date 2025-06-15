#pragma once

#include "MouseState.h"
#include "KeyboardState.h"

class IRendererGUI;
class IWidget;

/**
 * @brief Antarmuka utama untuk sistem GUI.
 * 
 * IGUI bertindak sebagai titik masuk utama sistem GUI. 
 * Ia bertanggung jawab untuk memperbarui logika (misalnya animasi dan interaksi),
 * merender elemen GUI menggunakan renderer agnostik (seperti IRendererGUI),
 * menangani input dari luar (mouse/keyboard), serta menyimpan dan mengatur widget-widget GUI.
 */
class IGUI {
public:
    virtual ~IGUI() {}

    /**
     * @brief Memperbarui logika GUI seperti animasi atau interaksi.
     * 
     * @param deltaTime Waktu dalam detik sejak frame terakhir.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Merender semua elemen GUI menggunakan renderer yang diberikan.
     * 
     * @param renderer Renderer GUI yang digunakan untuk menggambar elemen.
     */
    virtual void render(IRendererGUI* renderer) = 0;

    /**
     * @brief Menangani input dari mouse.
     * 
     * @param mouse State mouse saat ini (posisi, klik, dsb.).
     */
    virtual void onMouseInput(const MouseState& mouse) = 0;

    /**
     * @brief Menangani input dari keyboard.
     * 
     * @param keyboard State keyboard saat ini (key press, dsb.).
     */
    virtual void onKeyboardInput(const KeyboardState& keyboard) = 0;

    /**
     * @brief Menambahkan widget baru ke dalam GUI.
     * 
     * @param widget Pointer ke widget yang akan ditambahkan.
     */
    virtual void addWidget(IWidget* widget) = 0;

    /**
     * @brief Menghapus semua widget dari GUI.
     */
    virtual void clearWidgets() = 0;
};
