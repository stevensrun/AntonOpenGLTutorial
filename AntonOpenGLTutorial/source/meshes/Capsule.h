#pragma once

#include "Mesh.h"

class Capsule : public Mesh
{
public:
    Capsule(float height, float radius, int stackCount, int segmentCount);
    virtual ~Capsule() = default;
};