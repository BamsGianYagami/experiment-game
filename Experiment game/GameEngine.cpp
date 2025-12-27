#include "stdafx.h"
#include "GameEngine.h"

GameEngine::GameEngine()
    :
	inputManager(NULL),
	renderer(NULL), 
	platform(NULL),
	surface(NULL),
	audio(NULL) {}

GameEngine::~GameEngine() {
    shutdown();
}

void GameEngine::init() {
    std::cout << "Initializing engine...\n";

    // Input
    inputManager = new InputManager();

	//platform - gantinya window
	std::shared_ptr<WindowsPlatformLayer> windows = std::make_shared<WindowsPlatformLayer>();
	
	//pointing platform dan surface ke windows karena implementasi dari keduanya
	platform = windows;
	surface = windows;

	if (!surface->createSurface(sysConfig.video.resolution, L"My Game Window")) {
		std::cerr << "Failed to create surface.\n";
		return;
	}

	//cara memasang callback
	windows->setInputCallback(std::bind(&InputManager::CallBackInput, inputManager, std::placeholders::_1));


    // Renderer
    renderer = new OpenGLRenderer();
    if (!renderer->init(surface.get())) {
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
    //taruh di tengah layar
    uiElementTest->position = Vector2(sysConfig.video.resolution.x/2 - uiElementTest->size.x, sysConfig.video.resolution.y/2 - uiElementTest->size.y);
    uiElementTest->color = Color::Green();
	uiManager->AddRoot(uiElementTest);
	std::cout << "add UI element root "<< std::endl;

    //uji coba Audio
    #define AUDIO_PATH "D:/games/TSMOD.NET/valve/sound/weapons/xbow_hit1.wav"
    audio->loadSound("xbow", AUDIO_PATH);

    std::cout << "Engine initialized.\n";
}

void GameEngine::update() {

    if (platform) {
        platform->processPlatformEvents();
    }

    if (inputManager) {
        //inputManager->updateAllDevices();
        //debugInput();
    }

	// test moving
	#define MOVE_X 0.1f
	#define MOVE_Y 0.1f

	static float velX = MOVE_X;
	static float velY = MOVE_Y;

	// gerak
	uiElementTest->position.x += velX;
	uiElementTest->position.y += velY;

	// batas kanan & kiri
	float rightLimit = sysConfig.video.resolution.x - uiElementTest->size.x;

	if (uiElementTest->position.x >= rightLimit)
	{
		uiElementTest->position.x = rightLimit;
		velX = -velX; // MANTUL KANAN
		audio->playSound("xbow");
	}

	if (uiElementTest->position.x <= 0)
	{
		uiElementTest->position.x = 0;
		velX = -velX; // MANTUL KIRI
		audio->playSound("xbow");
	}

	// batas bawah & atas
	float bottomLimit = sysConfig.video.resolution.y - uiElementTest->size.y;

	if (uiElementTest->position.y >= bottomLimit)
	{
		uiElementTest->position.y = bottomLimit;
		velY = -velY; // MANTUL BAWAH
		audio->playSound("xbow");
	}

	if (uiElementTest->position.y <= 0)
	{
		uiElementTest->position.y = 0;
		velY = -velY; // MANTUL ATAS
		audio->playSound("xbow");
	}
	//end test moving

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

	//platform dan surface sekarang jadi shared pointer
	platform.reset();
	surface.reset();

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
