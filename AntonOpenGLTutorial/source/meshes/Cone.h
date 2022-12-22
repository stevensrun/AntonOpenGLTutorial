#pragma once

#include "Mesh.h"

class Cone : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Cone(float height, float radius, int stackCount, int segmentCount);
    virtual ~Cone() = default;
};