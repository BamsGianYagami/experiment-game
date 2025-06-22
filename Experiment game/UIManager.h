#pragma once
#include <vector>
#include "DrawCommand.h"
#include "UIElement.h"

using namespace GE;

class UIManager {
public:
    std::vector<UIElement*> roots;
    UIElement* focusedElement;

    UIManager();
    ~UIManager();

    void AddRoot(UIElement* elem);
    void RemoveRoot(UIElement* elem);

    void Update();
    std::vector<DrawCommand> DrawUI();

    void SetFocus(UIElement* elem);
    void DispatchClick(float px, float py);

    
private:
    UIElement* FindTopElement(UIElement* elem, float px, float py);
    std::vector<DrawCommand> drawCommandsUI;
};