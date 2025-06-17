#include "StdAfx.h"
#include "RenderManager.h"

namespace GE {
	RenderManager::RenderManager()
		: renderer(nullptr) {
	}

	RenderManager::~RenderManager() {
		clear();
	}

	void RenderManager::setRenderer(IRenderer* rendererInstance) {
		renderer = rendererInstance;
	}

	void RenderManager::DrawRect(const Vector2& position, const Vector2& size, const Color& color) {
		DrawCommand cmd;
		cmd.type = DrawCommand_Rect;
		cmd.position = position;
		cmd.size = size;
		cmd.color = color;
		guiCommands.push_back(cmd);
	}

	void RenderManager::DrawText(const std::string& text, const Vector2& position, float fontSize, const Color& color, int layer) {
		DrawCommand cmd;
		cmd.type = DrawCommand_Text;
		cmd.position = position;
		cmd.text = text;
		cmd.fontSize = fontSize;
		cmd.color = color;      // gunakan color untuk teks
		cmd.layer = layer;
		cmd.depthTest = false;  // biasanya teks tidak pakai depth test

		guiCommands.push_back(cmd);
	}

	void RenderManager::DrawMesh(int meshID, const Matrix4x4& transform) {
		DrawCommand cmd;
		cmd.type = DrawCommand_Mesh;
		cmd.meshID = meshID;
		cmd.transform = transform;
		cmd.depthTest = true;
		worldCommands.push_back(cmd);
	}

	void RenderManager::DrawLine(const Vector3& start, const Vector3& end, const Color& color) {
		DrawCommand cmd;
		cmd.type = DrawCommand_Line;
		cmd.position = Vector2(start.x, start.y);  // sementara (untuk 2D compat)
		cmd.size = Vector2(end.x - start.x, end.y - start.y); // representasi garis
		cmd.wireColor = color;
		cmd.depthTest = true;
		worldCommands.push_back(cmd);
	}

	void RenderManager::flush() {
		if (!renderer) return;

		renderer->Begin3D();
		for (std::vector<DrawCommand>::iterator it = worldCommands.begin(); it != worldCommands.end(); ++it) {
			renderer->Execute(*it);
		}
		renderer->End3D();

		renderer->Begin2D();
		for (std::vector<DrawCommand>::iterator it = guiCommands.begin(); it != guiCommands.end(); ++it) {
			renderer->Execute(*it);
		}
		renderer->End2D();

		worldCommands.clear();
		guiCommands.clear();
	}

	void RenderManager::clear() {
		worldCommands.clear();
		guiCommands.clear();
	}
}


/* Contoh pseudocode pemakaian di aplikasi utama:
RenderManager renderMgr;
OpenGLRenderer glRenderer;
IWindow* window = ...;

glRenderer.init(window);
renderMgr.setRenderer(&glRenderer);

// Per frame:
renderMgr.DrawRect({100, 100}, {200, 50}, {1, 0, 0, 1});
renderMgr.DrawRect({300, 200}, {100, 100}, {0, 1, 0, 1});

renderMgr.flush();  // jalankan semua perintah
glRenderer.render(); // swap buffers
*/