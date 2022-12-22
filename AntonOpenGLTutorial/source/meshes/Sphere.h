#pragma once

#include "Mesh.h"

class Sphere : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Sphere(float radius, int stackCount, int segmentCount);
    virtual ~Sphere() = default;
};