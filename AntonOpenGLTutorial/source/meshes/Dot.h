#pragma once

#include "Mesh.h"

class Dot : public Mesh
{
public:
    Dot();
    virtual ~Dot() = default;

    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal) override;
    virtual void Draw(ShaderManager* shaderManager) const override;
};