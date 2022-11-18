#pragma once

#include "Mesh.h"

class Plane : public Mesh
{
public:
    Plane(int rows, int columns);
    virtual ~Plane() = default;
};