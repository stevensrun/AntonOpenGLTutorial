#pragma once

#include "Mesh.h"

class Plane : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Plane(int rows, int columns);
    virtual ~Plane() = default;
};