#pragma once
#include <vector>
#include "MathTypes.h"
#include "DrawCommand.h"

using namespace GE;
class UIElement {
public:
    UIElement* parent;
    std::vector<UIElement*> children;

    Vector2 position;
    Vector2 size;
	Color color;

    bool isVisible;
    bool isFocused;

	UIElement();
    virtual ~UIElement();

    virtual void AddChild(UIElement* child);
    virtual void RemoveChild(UIElement* child);

    virtual void Update();
    virtual void Draw(std::vector<DrawCommand>& commands);

    virtual DrawCommand UIElement::DrawSelf(); // Override this in subclasses

    virtual void OnFocus();
    virtual void OnUnfocus();
    virtual void OnSelected();

    virtual bool HitTest(float px, float py) const;
};