#pragma once

#include "InputManager.h"
#include "IRenderer.h"
#include "IWindow.h"
#include "IAudio.h"

#include "KeyCode.h"

#include "KeyboardInputDevice.h"
#include "MouseInputDevice.h"

#include "WindowsKeyboardBackend.h"
#include "WindowsMouseBackend.h"
#include "OpenGLRenderer.h"
#include "WindowManagerWin32.h"
#include "OpenALAudio.h"

#include "RenderManager.h"      // agar bisa SubmitCommand
#include "DrawCommand.h"
#include "UIManager.h"

#include "MathTypes.h"          // Vector2, dll

#include "SystemConfig.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void init();
	/*
	Sekarang window menggunakan interface IWindow,
	dan implementasi Windows mengambil HINSTANCE sendiri.
	Jadi tidak perlu lagi passing HINSTANCE dari entry point.
	*/
	//void init(HINSTANCE hInstance);
    void update();
    void shutdown();

	SystemConfig sysConfig;

private:
    InputManager* inputManager;
    IRenderer* renderer;
	IWindow* window;
	IAudio* audio;
	KeyboardInputDevice* keyboard;
	MouseInputDevice* mouse;
	RenderManager* renderManager;
	UIManager* uiManager;

	void debugInput();   // Fungsi bantu debugging input
    void debugRender();  // Fungsi bantu submit dan render GUI test
	// void debugUI(); //Fungsi bantu test uiManager

	UIElement* uiElementTest; //object bantu test uiManager
};