#pragma once

#include <vector>
#include "DrawCommand.h"
#include "IRenderer.h"

namespace GE {
	/**
	 * @brief Manajer utama untuk mengatur dan mengirim perintah rendering ke renderer.
	 * Bertugas menampung draw command dan melakukan submit di akhir frame.
	 */
	class RenderManager {
	public:
		RenderManager();
		~RenderManager();

		/**
		 * @brief Mengatur renderer backend yang digunakan untuk mengeksekusi command.
		 */
		void setRenderer(IRenderer* renderer);

		// API Tingkat Tinggi untuk GUI
		/**
		 * @brief Menambahkan perintah DrawRect ke antrian.
		 */
		void DrawRect(const Vector2& position, const Vector2& size, const Color& color);
		/**
		 * @brief Menambahkan perintah DrawText ke antrian.
		 */
		void DrawText(const std::string& text, const Vector2& position, float fontSize, const Color& color, int layer = 0);

		// API untuk 3D (nanti bisa ditambah: DrawMesh, DrawLine, dll)
		void DrawMesh(int meshID, const Matrix4x4& transform);
		void DrawLine(const Vector3& start, const Vector3& end, const Color& color);


		/**
		 * @brief Menjalankan semua draw command dan mengosongkan antrian.
		 * Harus dipanggil sebelum render::render() untuk memastikan semua command dieksekusi.
		 */
		void flush();

		/**
		 * @brief Menghapus semua command tanpa menjalankan render (jika perlu dibatalkan).
		 */
		void clear();

	private:
		void renderWorld();
		void renderOverlay();
		void render2D();
		IRenderer* renderer;
		std::vector<DrawCommand> twoDCommands;
		std::vector<DrawCommand> worldCommands;
		std::vector<DrawCommand> overlayCommands;
	};

}