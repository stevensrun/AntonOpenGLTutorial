#pragma once

#include "Mesh.h"

class Dot : public Mesh
{
public:
    Dot();
    virtual ~Dot() = default;

    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal) override;
    virtual bool HitTest(TriangleShape*& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface) const override;
    virtual void Draw(ShaderManager* shaderManager) const override;
};