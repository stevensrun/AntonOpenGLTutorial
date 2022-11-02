#pragma once

#include "Mesh.h"

class Triangle : public Mesh
{
public:
    Triangle();
    virtual ~Triangle() = default;

    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal) override;
    virtual void Draw() override;

private:
    float m_t;
};