#pragma once

#include "Mesh.h"

class Torus : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Torus(float majorRadius, float minorRadius, int stackCount, int segmentCount);
    virtual ~Torus() = default;
};