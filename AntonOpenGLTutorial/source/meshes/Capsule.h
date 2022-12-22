#pragma once

#include "Mesh.h"

class Capsule : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Capsule(float height, float radius, int stackCount, int segmentCount);
    virtual ~Capsule() = default;
};