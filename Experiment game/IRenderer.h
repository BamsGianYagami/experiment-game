#pragma once

class IWindow;

class IRenderer {
public:
    virtual ~IRenderer() {}

    virtual bool init(IWindow* IWindow) = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;
};
