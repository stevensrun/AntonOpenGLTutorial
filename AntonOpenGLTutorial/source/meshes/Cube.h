#pragma once

#include "Mesh.h"

class Cube : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Cube(int stackCount, int segmentCount);
    virtual ~Cube()= default;
};