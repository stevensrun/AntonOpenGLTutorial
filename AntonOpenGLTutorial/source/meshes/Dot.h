#pragma once

#include "Mesh.h"

class Dot : public Mesh
{
public:
    Dot() = default;
    virtual ~Dot() = default;

    virtual float GetIntersectionParameter(const glm::vec3 rayOrigin, const glm::vec3& rayDirection) override;
    virtual void Draw() override;
};