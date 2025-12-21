#pragma once

#include "InputManager.h"
#include "IRenderer.h"
//#include "IWindow.h"
#include "IPlatformLayer.h"
#include "IAudio.h"

#include "KeyCode.h"

#include "OpenGLRenderer.h"
//#include "WindowManagerWin32.h"
#include "WindowsPlatformLayer.h"
#include "OpenALAudio.h"

#include "RenderManager.h"      // agar bisa SubmitCommand
#include "UIManager.h"

#include "MathTypes.h"          // Vector2, dll

#include "SystemConfig.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void init();
	/*
	Sekarang window menggunakan interface IRenderSurface,
	dan implementasi Windows mengambil HINSTANCE sendiri.
	Jadi tidak perlu lagi passing HINSTANCE dari entry point.
	GetModuleHandle() juga sama mengambil alamat dari entry point main windows
	*/
	//void init(HINSTANCE hInstance);
    void update();
    void shutdown();

	SystemConfig sysConfig;

private:
    InputManager* inputManager;
    IRenderer* renderer;
	std::shared_ptr<IPlatformLayer> platform;
	std::shared_ptr<IRenderSurface> surface;
	IAudio* audio;
	RenderManager* renderManager;
	UIManager* uiManager;

	void debugInput();   // Fungsi bantu debugging input
    void debugRender();  // Fungsi bantu submit dan render GUI test
	// void debugUI(); //Fungsi bantu test uiManager

	UIElement* uiElementTest; //object bantu test uiManager
};