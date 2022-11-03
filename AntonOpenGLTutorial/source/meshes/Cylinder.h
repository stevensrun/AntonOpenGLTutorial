#pragma once

#include "Mesh.h"

class Cylinder : public Mesh
{
public:
    Cylinder(float height, float radius, int stackCount, int segmentCount);
    virtual ~Cylinder() = default;
};