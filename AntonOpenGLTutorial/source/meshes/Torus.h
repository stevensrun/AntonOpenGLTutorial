#pragma once

#include "Mesh.h"

class Torus : public Mesh
{
public:
    Torus(float majorRadius, float minorRadius, int stackCount, int segmentCount);
    virtual ~Torus() = default;

};