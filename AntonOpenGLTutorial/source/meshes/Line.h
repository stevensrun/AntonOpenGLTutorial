#pragma once

#include "Mesh.h"

class Line : public Mesh
{
public:
    Line(const glm::vec3& p0, const glm::vec3 p1);
    virtual ~Line() = default;

    virtual void Draw(ShaderManager* shaderManager, Camera* camera, Light* light) override;
};