#pragma once

#include "Mesh.h"

class Triangle : public Mesh
{
public:
    Triangle() = default;
    virtual ~Triangle() = default;

    virtual float GetIntersectionParameter(const glm::vec3 rayOrigin, const glm::vec3& rayDirection) override;
    virtual void AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute = false) override;
    virtual void Draw() override;

private:
    glm::vec3 m_normal;
};