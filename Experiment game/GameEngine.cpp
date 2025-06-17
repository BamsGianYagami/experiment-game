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
    if (!window->create(800, 600, L"My Game Window")) {
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

void GameEngine::debugRender() {
    renderer->beginFrame();

    // Hardcoded posisi tengah window 800x600
    // Rect berukuran 200x50 di tengah
    renderManager->DrawRect(Vector2(300, 275), Vector2(200, 50), Color::White());

    // Teks kira-kira berada di dalam rect (tidak presisi tengah teks)
    renderManager->DrawText("Halo Dunia Penuh Derita", Vector2(310, 305), 18.0f, Color::Black());

    renderManager->flush();
    renderer->endFrame();
}
