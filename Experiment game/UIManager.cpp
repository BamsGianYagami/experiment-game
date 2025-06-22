#include "StdAfx.h"
#include "UIManager.h"

//
// UIManager
//
UIManager::UIManager() : focusedElement(0) {
	drawCommandsUI.reserve(1024); // kapasitas awal
}

UIManager::~UIManager() {}

void UIManager::AddRoot(UIElement* elem) {
    roots.push_back(elem);
}

void UIManager::RemoveRoot(UIElement* elem) {
    for (std::vector<UIElement*>::iterator it = roots.begin();
         it != roots.end(); ++it) {
        if (*it == elem) {
            roots.erase(it);
            break;
        }
    }
}

void UIManager::Update() {
	drawCommandsUI.clear();
    for (size_t i = 0; i < roots.size(); ++i) {
        roots[i]->Update();
    }
}

std::vector<DrawCommand> UIManager::DrawUI() {
    for (size_t i = 0; i < roots.size(); ++i) {
        roots[i]->Draw(drawCommandsUI);
    }
	return drawCommandsUI;
}

void UIManager::SetFocus(UIElement* elem) {
    if (focusedElement == elem) return;
    if (focusedElement) focusedElement->OnUnfocus();
    focusedElement = elem;
    if (focusedElement) focusedElement->OnFocus();
}

UIElement* UIManager::FindTopElement(UIElement* elem, float px, float py) {
    for (int i = (int)elem->children.size() - 1; i >= 0; --i) {
        UIElement* hit = FindTopElement(elem->children[i], px, py);
        if (hit) return hit;
    }
    return elem->HitTest(px, py) ? elem : 0;
}

void UIManager::DispatchClick(float px, float py) {
    UIElement* target = 0;
    for (size_t i = 0; i < roots.size(); ++i) {
        UIElement* hit = FindTopElement(roots[i], px, py);
        if (hit) target = hit;
    }
    if (target) {
        SetFocus(target);
        target->OnSelected();
    }
}