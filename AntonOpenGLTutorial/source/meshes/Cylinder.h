#pragma once

#include "Mesh.h"

class Cylinder : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Cylinder(float height, float radius, int stackCount, int segmentCount);
    virtual ~Cylinder() = default;
};