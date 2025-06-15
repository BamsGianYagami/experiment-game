#include "stdafx.h"
#include "GameEngine.h"

GameEngine::GameEngine() : inputManager(NULL), renderer(NULL), window(NULL) {}


GameEngine::~GameEngine() {
    shutdown();
}

void GameEngine::init() {
    std::cout << "Initializing engine...\n";

	inputManager = new InputManager();
	
	keyboard = new KeyboardInputDevice(new WindowsKeyboardBackend());
	inputManager->registerDevice(keyboard);
	
	mouse = new MouseInputDevice(new WindowsMouseBackend());
	inputManager->registerDevice(mouse);

	
	window = new WindowManagerWin32();
    if (!window->create(800, 600, L"My Game Window")) {   // gunakan create()
        std::cerr << "Failed to create window.\n";
        return;
    }

	// Renderer sekarang diinisialisasi dengan IWindow*, bukan handle spesifik platform.
	// Ini memungkinkan engine tetap agnostik terhadap platform (Win32 / Android / dst).
	renderer = new OpenGLRenderer();
    if (!renderer->init(window)) {
        std::cerr << "Failed to initialize OpenGL\n";
        return;
    }

	audio = new OpenALAudio();
	if(!audio->init()){
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
        inputManager->updateAllDevices();  // polling input

        // --- Debugging Keyboard ---
        KeyboardInputDevice* keyboard = inputManager->getKeyboard();
        if (keyboard->isKeyDown(Key_ENTER)) {
            std::cout << "Enter baru ditekan!\n";
        }
        if (keyboard->isKeyUp(Key_SPACE)) {
            std::cout << "Space baru dilepas!\n";
        }
        if (keyboard->isKeyHeld(Key_A)) {
            std::cout << "A sedang ditekan terus.\n";
        }

        // --- Debugging Mouse ---
        MouseInputDevice* mouse = inputManager->getMouse();
        const MouseState& currentMouse = mouse->getState();
        const MouseDeltaState& delta = mouse->getDelta();

        // Contoh tombol mouse5
        if (mouse->isMouseDown(MouseButton::Mouse5)) {
            std::cout << "mouse5Button baru ditekan\n";
        }
        if (mouse->isMouseUp(MouseButton::Mouse5)) {
            std::cout << "mouse5Button baru dilepas\n";
        }
        if (mouse->isMouseHeld(MouseButton::Mouse5)) {
            std::cout << "mouse5Button sedang ditekan terus\n";
        }

        // Pergerakan mouse
        if (delta.deltaX != 0 || delta.deltaY != 0) {
            std::cout << "Mouse moved: Δx = " << delta.deltaX << ", Δy = " << delta.deltaY << "\n";
        }
    }

    if (renderer) {
        renderer->render();  // menggambar frame
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

    std::cout << "Engine shutdown complete.\n";
}
