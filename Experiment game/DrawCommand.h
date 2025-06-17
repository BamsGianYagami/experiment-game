#pragma once

#include <string>
#include "MathTypes.h" // Contain Vector2, Vector3, Color, Matrix4x4, etc.

namespace GE { // Game Engine namespace untuk menghindari konflik

	/**
	 * @brief Jenis draw command yang bisa dieksekusi oleh renderer.
	 */
	enum DrawCommandType {
		DrawCommand_None = 0,
        DrawCommand_Rect,
        DrawCommand_Text,
        DrawCommand_Mesh,
        DrawCommand_Line,
		//tambahkan sesuai kebutuhan
    };

	/**
	 * @brief Struktur data generik untuk menggambarkan satu instruksi render.
	 * 
	 * Struktur ini digunakan oleh RenderManager dan dieksekusi oleh IRenderer.
	 */
	struct DrawCommand {
		DrawCommandType type;

		// Digunakan oleh GUI (DrawRect, DrawText)
		Vector2 position;
		Vector2 size;
		Color color;
		std::string text;
		float fontSize;

		// Digunakan oleh dunia 3D (DrawMesh, DrawLine)
		int meshID;             // ID dari resource mesh
		Matrix4x4 transform;    // Transformasi dunia
		Color wireColor;        // Untuk debug line

		// Opsi umum
		int layer;              // Untuk sorting (misal GUI)
		bool depthTest;         // Aktif/nonaktif depth

		// Konstruktor default
		DrawCommand()
			: type(DrawCommand_None),
			  position(0, 0),
			  size(0, 0),
			  color(1, 1, 1, 1),
			  text(""),
			  fontSize(16.0f),
			  meshID(-1),
			  transform(Matrix4x4::Identity()),
			  wireColor(1, 1, 1, 1),
			  layer(0),
			  depthTest(true)
		{}
	};

} // namespace GE


/*sample draw command:
DrawCommand rect;
rect.type = DrawCommandType::DrawRect;
rect.position = Vector2(100, 100);
rect.size = Vector2(200, 50);
rect.color = Color::Red();

renderManager.SubmitGUICommand(rect);

*/