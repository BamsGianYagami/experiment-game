#pragma once

#include "DrawCommand.h"
#include "IWindow.h"

using namespace GE;

/**
 * @brief Interface abstrak untuk sistem renderer backend (OpenGL, Vulkan, Software, dsb).
 */
class IRenderer {
public:
    virtual ~IRenderer() {}

    /**
     * @brief Inisialisasi renderer dengan window target.
     * @param window Pointer ke IWindow (sudah memiliki native handle).
     */
    virtual bool init(IWindow* window) = 0;

    /**
     * @brief Memulai pipeline render (biasanya hanya glClear dan glClearColor.
     */
	virtual void beginFrame() = 0;

	/**
     * @brief Mengakhiri pipeline render (biasanya hanya swap buffer).
     */
	virtual void endFrame() = 0;

    /**
     * @brief Membersihkan resource dan menghentikan renderer.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Menjalankan perintah rendering spesifik seperti menggambar rect, mesh, dll.
     * @param command Struktur perintah rendering (DrawCommand).
     */
    virtual void Execute(const DrawCommand& command) = 0;

	// Untuk mengatur konteks 2D dan 3D rendering
	virtual void Begin2D() = 0;
	virtual void End2D() = 0;
	virtual void Begin3D() = 0;
	virtual void End3D() = 0;
};
