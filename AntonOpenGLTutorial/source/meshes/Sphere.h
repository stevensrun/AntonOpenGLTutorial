#pragma once

#include "Mesh.h"

class Sphere : public Mesh
{
public:
    Sphere(float radius, int stackCount, int segmentCount);
    virtual ~Sphere() = default;
};