#pragma once

#include "Mesh.h"

class Line : public BasicMesh
{
public:
    Line(const glm::vec3& p0, const glm::vec3 p1);
    virtual ~Line() = default;

    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const override;
};