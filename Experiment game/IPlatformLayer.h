#pragma once

#include "MathTypes.h"

class IPlatformLayer {
public:
    virtual void processPlatformEvents() = 0;
    virtual ~IPlatformLayer() {}
};