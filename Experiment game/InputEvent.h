// InputEvent.h
#pragma once
#include "MouseButton.h"

namespace GE {
	enum InputEventType {
		KeyDown,
		KeyUp,
		MouseButtonDown,
		MouseButtonUp,
		MouseMove,
		MouseWheel
	};

	/*
	enum MouseButton {
		Left,
		Right,
		Middle,
		X1,
		X2
	};*/

	struct InputEvent {
		InputEventType type;
		int keyOrButton;    // keycode untuk keyboard, index untuk mouse
		MouseButton mouseButton; // hanya valid untuk MouseButtonDown/Up
		int x;
		int y;
		int scrollDelta;
	};

}