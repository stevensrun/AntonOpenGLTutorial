#pragma once

#include "Mesh.h"

class SierpinskiGasket : public Mesh
{
public:
    SierpinskiGasket(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int pointCount);
    ~SierpinskiGasket() = default;

    virtual bool HitTest(TriangleShape*& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface = false) const;
    virtual void Draw(ShaderManager* shaderManager) const;
};