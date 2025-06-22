#include "StdAfx.h"
#include "RenderManager.h"

namespace GE {
	RenderManager::RenderManager()
		: renderer(nullptr) {
	}

	RenderManager::~RenderManager() {
		//clear();
	}

	void RenderManager::setRenderer(IRenderer* rendererInstance) {
		renderer = rendererInstance;
	}

	//sample untuk kebutuhan testing
	// void RenderManager::DrawRect(const Vector2& position, const Vector2& size, const Color& color) {
	// 	DrawCommand cmd;
	// 	cmd.type = DrawCommand_Rect;
	// 	cmd.position = position;
	// 	cmd.size = size;
	// 	cmd.color = color;
	// 	twoDCommands.push_back(cmd);
	// }

	//sample untuk kebutuhan testing
	// void RenderManager::DrawText(const std::string& text, const Vector2& position, float fontSize, const Color& color, int layer) {
	// 	DrawCommand cmd;
	// 	cmd.type = DrawCommand_Text;
	// 	cmd.position = position;
	// 	cmd.text = text;
	// 	cmd.fontSize = fontSize;
	// 	cmd.color = color;      // gunakan color untuk teks
	// 	cmd.layer = layer;
	// 	cmd.depthTest = false;  // biasanya teks tidak pakai depth test

	// 	twoDCommands.push_back(cmd);
	// }

	// void RenderManager::DrawMesh(int meshID, const Matrix4x4& transform) {
	// 	DrawCommand cmd;
	// 	cmd.type = DrawCommand_Mesh;
	// 	cmd.meshID = meshID;
	// 	cmd.transform = transform;
	// 	cmd.depthTest = true;
	// 	worldCommands.push_back(cmd);
	// }

	// void RenderManager::DrawLine(const Vector3& start, const Vector3& end, const Color& color) {
	// 	DrawCommand cmd;
	// 	cmd.type = DrawCommand_Line;
	// 	cmd.position = Vector2(start.x, start.y);  // sementara (untuk 2D compat)
	// 	cmd.size = Vector2(end.x - start.x, end.y - start.y); // representasi garis
	// 	cmd.wireColor = color;
	// 	cmd.depthTest = true;
	// 	worldCommands.push_back(cmd);
	// }

	void RenderManager::RenderWorld(const std::vector<DrawCommand>& cmds){
		renderer->Begin3D();
		for (std::vector<DrawCommand>::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
			renderer->Execute(*it);
		}
		renderer->End3D();
	}

	void RenderManager::RenderOverlay(const std::vector<DrawCommand>& cmds){
		renderer->BeginOverlay();
		for (std::vector<DrawCommand>::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
			renderer->Execute(*it);
		}
		renderer->EndOverlay();
	}

	void RenderManager::RenderUI(const std::vector<DrawCommand>& cmds){
		renderer->Begin2D();
		for (std::vector<DrawCommand>::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
			renderer->Execute(*it);
		}
		renderer->End2D();
	}

	//ini untuk testing saja, akan diubah pipeline nya
	// void RenderManager::flush() {
	// 	if (!renderer) return;

	// 	// --- PASS 1: Dunia 3D (dengan depth test & depth write)
	// 	if(!worldCommands.empty())
	// 		renderWorld();

	// 	// --- PASS 2: Overlay 3D atau HUD (depth test khusus, no depth write)
	// 	if(!overlayCommands.empty())
	// 		renderOverlay();

	// 	// --- PASS 3: GUI 2D (tanpa depth sama sekali, pure ortho)
	// 	if(!twoDCommands.empty())
	// 		render2D();
		

	// 	worldCommands.clear();
	// 	overlayCommands.clear();
	// 	twoDCommands.clear();
	// }

	// void RenderManager::clear() {
	// 	worldCommands.clear();
	// 	overlayCommands.clear();
	// 	twoDCommands.clear();
	// }
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