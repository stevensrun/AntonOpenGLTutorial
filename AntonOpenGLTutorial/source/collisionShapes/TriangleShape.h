#pragma once

#include <glm/glm.hpp>

class TriangleShape
{
public:
    TriangleShape(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    ~TriangleShape() = default;

    bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal);

private:
    glm::vec3 m_a;
    glm::vec3 m_b;
    glm::vec3 m_c;
    glm::vec3 m_normal;
};