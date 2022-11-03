#pragma once

#include "Mesh.h"

class Cone : public Mesh
{
public:
    Cone(float height, float radius, int stackCount, int segmentCount);
    virtual ~Cone() = default;
};