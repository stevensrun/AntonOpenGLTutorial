#pragma once

#include "Mesh.h"

class Dot : public Mesh
{
public:
    Dot();
    virtual ~Dot() = default;

    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal) const override;
    virtual void Draw(ShaderManager* shaderManager) const override;
};