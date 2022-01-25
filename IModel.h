#pragma once

#include <string>

#include "Primitives.h"

class IUseCase {
public:
    virtual ~IUseCase() = default;
    virtual void addPrimitive(Primitive primitive) = 0;
    virtual void removePrimitive(const Primitive& primitive) = 0;
    virtual void saveTo(std::string filename) = 0;
    virtual void loadFrom(std::string filename) = 0;
};