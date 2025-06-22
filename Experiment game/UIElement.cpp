#include "StdAfx.h"
#include "UIElement.h"

//
// UIElement Implementation
//
UIElement::UIElement() : parent(0), isVisible(true), isFocused(false) {
	 position = Vector2(0, 0);
	 size = Vector2(100, 50);
}

UIElement::~UIElement() {
    // Kalau mau bersihkan sesuatu, taruh di sini.
}

void UIElement::AddChild(UIElement* child) {
    child->parent = this;
    children.push_back(child);
}

void UIElement::RemoveChild(UIElement* child) {
    for (std::vector<UIElement*>::iterator it = children.begin();
         it != children.end(); ++it) {
        if (*it == child) {
            children.erase(it);
            child->parent = 0;
            break;
        }
    }
}

void UIElement::Update() {
    for (size_t i = 0; i < children.size(); ++i) {
        children[i]->Update();
    }
}

void UIElement::Draw(std::vector<DrawCommand>& commands) {
	if (!isVisible) return;
		commands.push_back(DrawSelf());
        // gambar element child
        for (size_t i = 0; i < children.size(); ++i) {
            children[i]->Draw(commands); // pass by ref
        }
}

DrawCommand UIElement::DrawSelf() {
    // buat drawCommand sesuai elemen
    DrawCommand rectCmd;
    rectCmd.type = DrawCommand_Rect;
	rectCmd.position = position;
	rectCmd.size = size;
	rectCmd.color = color;
    return rectCmd;
}

void UIElement::OnFocus() {
    isFocused = true;
}

void UIElement::OnUnfocus() {
    isFocused = false;
}

void UIElement::OnSelected() {
    // Default action
}

bool UIElement::HitTest(float px, float py) const {
    return isVisible &&
		(px >= position.x && px <= position.x + size.x) &&
           (py >= position.y && py <= position.y + size.y);
}