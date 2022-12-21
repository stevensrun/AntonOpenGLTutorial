#pragma once

#include <glm/glm.hpp>
#include "meshes/Mesh.h"


class TriangleShape : public Mesh
{
public:
    TriangleShape(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    virtual ~TriangleShape() = default;

    bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface);
    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const override;
};