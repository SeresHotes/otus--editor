#pragma once

#include "Primitives.h"

class IViewModel {
public:
    virtual ~IViewModel() = default;
    virtual void messageAddPrimitive(const Primitive& primitive) = 0;
    virtual void messageRemovePrimitive(const Primitive& primitive) = 0;
};
