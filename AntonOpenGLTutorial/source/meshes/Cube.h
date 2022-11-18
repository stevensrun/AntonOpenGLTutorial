#pragma once

#include "Mesh.h"

class Cube : public Mesh
{
public:
    Cube(int rows, int columns);
    virtual ~Cube()= default;
};