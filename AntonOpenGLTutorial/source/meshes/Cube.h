#pragma once

#include "Mesh.h"

class Cube : public Mesh
{
public:
    Cube(int stackCount, int segmentCount);
    virtual ~Cube()= default;
};