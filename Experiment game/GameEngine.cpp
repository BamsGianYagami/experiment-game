#include "stdafx.h"
#include "GameEngine.h"

GameEngine::GameEngine()
    : inputManager(NULL), renderer(NULL), window(NULL), audio(NULL) {}

GameEngine::~GameEngine() {
    shutdown();
}

void GameEngine::init() {
    std::cout << "Initializing engine...\n";

    // Input
    inputManager = new InputManager();
    keyboard = new KeyboardInputDevice(new WindowsKeyboardBackend());
    mouse = new MouseInputDevice(new WindowsMouseBackend());
    inputManager->registerDevice(keyboard);
    inputManager->registerDevice(mouse);

    // Window
    window = new WindowManagerWin32();
	if (!window->create(sysConfig.video.resolution, L"My Game Window")) {
        std::cerr << "Failed to create window.\n";
        return;
    }

    // Renderer
    renderer = new OpenGLRenderer();
    if (!renderer->init(window)) {
        std::cerr << "Failed to initialize OpenGL\n";
        return;
    }

	renderManager = new RenderManager();
    renderManager->setRenderer(renderer);  // inject renderer ke pipeline

    // Audio
    audio = new OpenALAudio();
    if (!audio->init()) {
        std::cerr << "Failed to initialize OpenAL\n";
        return;
    }

	//UI
	uiManager = new UIManager();
    //ini hanya untuk uji coba
	uiElementTest = new UIElement();
	uiManager->AddRoot(uiElementTest);
	std::cout << "add UI element root "<< std::endl;

    std::cout << "Engine initialized.\n";
}

void GameEngine::update() {
    if (window) {
        window->processEvents();
    }

    if (inputManager) {
        inputManager->updateAllDevices();
        debugInput();
    }

	if(uiManager){
		uiManager->Update();
	}

    if (renderer) {
        debugRender();
    }
}

void GameEngine::shutdown() {
    std::cout << "Shutting down engine...\n";

    if (inputManager) {
        delete inputManager;
        inputManager = NULL;
    }

    if (renderer) {
        delete renderer;
        renderer = NULL;
    }

    if (window) {
        delete window;
        window = NULL;
    }

    if (audio) {
        delete audio;
        audio = NULL;
    }

	if(renderManager){
		delete renderManager;
		renderManager = NULL;
	}

	if(uiManager){
		delete uiManager;
		uiManager = NULL;
	}

    std::cout << "Engine shutdown complete.\n";
}

// ===================
// 🔍 Fungsi Debug
// ===================

void GameEngine::debugInput() {
    // Keyboard
    if (keyboard->isKeyDown(Key_ENTER)) {
        std::cout << "Enter baru ditekan!\n";
    }
    if (keyboard->isKeyUp(Key_ENTER)) {
        std::cout << "Enter baru dilepas!\n";
    }
    if (keyboard->isKeyHeld(Key_ENTER)) {
        std::cout << "Enter sedang ditahan.\n";
    }

    // Mouse
    const MouseState& currentMouse = mouse->getState();
    const MouseDeltaState& delta = mouse->getDelta();

    if (mouse->isMouseDown(GE::MouseButton_Mouse5)) {
        std::cout << "mouse5Button baru ditekan\n";
    }
    if (mouse->isMouseUp(GE::MouseButton_Mouse5)) {
        std::cout << "mouse5Button baru dilepas\n";
    }
    if (mouse->isMouseHeld(GE::MouseButton_Mouse5)) {
        std::cout << "mouse5Button sedang ditahan\n";
    }

    if (delta.deltaX != 0 || delta.deltaY != 0) {
        std::cout << "Mouse moved: DeltaX = " << delta.deltaX << ", DeltaY = " << delta.deltaY << "\n";
    }
}

// void GameEngine::debugRender() {
//     float screenW = sysConfig.video.resolution.x;
//     float screenH = sysConfig.video.resolution.y;

//     std::string text = "Halo Dunia Penuh Derita";
//     float fontSize = 18.0f;

//     // Ukuran teks
//     float charWidth = fontSize * 0.52f; //todo: tiap string karakternya panjangnya gak selalu sama, butuh database lebar per karakter.
//     float charHeight = fontSize;
//     float textW = charWidth * text.length();
//     float textH = charHeight;

//     // Padding per sisi
//     float paddingLeft   = 4.0f;
//     float paddingRight  = 8.0f;
//     float paddingTop    = 2.0f;
//     float paddingBottom = 2.0f;

//     // Ukuran rect
//     float rectW = textW + paddingLeft + paddingRight;
//     float rectH = textH + paddingTop + paddingBottom;

//     // Posisi rect center
//     float rectX = (screenW - rectW) * 0.5f;
//     float rectY = (screenH - rectH) * 0.5f;

//     // Vertical baseline offset
//     float ascent = fontSize * 0.8f;
//     float descent = fontSize * 0.2f;
//     float baselineY = rectY + rectH * 0.5f + (ascent - (ascent + descent) * 0.5f);

//     // Posisi teks (dari rect top-left)
//     float textX = rectX + paddingLeft;

//     // Draw
//     renderer->beginFrame();
//     renderManager->DrawRect(Vector2(rectX, rectY), Vector2(rectW, rectH), Color::Red());
//     renderManager->DrawText(text, Vector2(textX, baselineY), fontSize, Color::White());
//     renderManager->flush();
//     renderer->endFrame();
// }

void GameEngine::debugRender(){
    // Render
    renderer->beginFrame();

    // Dunia 3D
    //renderManager.RenderWorld(worldManager.GetDrawCommandList());

    // Overlay (opsional kalau mau dipisah)
    //renderManager.RenderOverlay(overlayManager.GetDrawCommandList());

    // UI 2D
    renderManager->RenderUI(uiManager->DrawUI());

    renderer->endFrame();
}
