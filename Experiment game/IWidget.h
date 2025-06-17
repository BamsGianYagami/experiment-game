#pragma once
#include <cstdint>
#include "IRendererGUI.h"


/**
 * @interface IWidget
 * @brief Interface dasar untuk semua elemen GUI individual dalam sistem GUI.
 *
 * IWidget mewakili satu komponen GUI seperti tombol, label, atau slider.
 * Interface ini menyediakan kontrak umum untuk posisi, ukuran, status interaksi
 * (hover, fokus, enabled), serta logika update dan rendering.
 *
 * Semua jenis widget harus mengimplementasikan interface ini agar dapat digunakan
 * secara seragam oleh sistem GUI dan renderer.
 *
 * @see IRendererGUI, IGUI
 */

class IWidget {
public:
	virtual ~IWidget() {};

    // Ukuran dan posisi
    virtual void SetPosition(float x, float y) = 0;
    virtual void SetSize(float width, float height) = 0;
    virtual float GetX() const = 0;
    virtual float GetY() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    // Logika dan update
    virtual void Update(float deltaTime) = 0;

    // Rendering
    virtual void Render(IRendererGUI* renderer) = 0;

    // Interaksi
    virtual void SetHovered(bool hovered) = 0;
    virtual bool IsHovered() const = 0;

    // (Optional) Fokus & aktif
    virtual void SetFocused(bool focused) = 0;
    virtual bool IsFocused() const = 0;
    virtual void SetEnabled(bool enabled) = 0;
    virtual bool IsEnabled() const = 0;
};
