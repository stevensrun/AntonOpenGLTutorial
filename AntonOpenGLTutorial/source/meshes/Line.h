#pragma once

#include "Mesh.h"

class Line : public Mesh
{
public:
    Line(const glm::vec3& p0, const glm::vec3 p1);
    virtual ~Line() = default;

    virtual bool HitTest(TriangleShape*& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface = false) const;
    virtual void Draw(ShaderManager* shaderManager) const override;
};