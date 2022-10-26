#pragma once

#include "Mesh.h"

class Dot : public Mesh
{
public:
    Dot();
    virtual ~Dot() = default;

    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal) override;
    virtual void Draw() override;
};