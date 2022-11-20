#pragma once

#include "Mesh.h"

class SierpinskiGasket : public BasicMesh
{
public:
    SierpinskiGasket(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int pointCount);
    ~SierpinskiGasket() = default;

    virtual void Draw(ShaderManager* shaderManager) const;
};