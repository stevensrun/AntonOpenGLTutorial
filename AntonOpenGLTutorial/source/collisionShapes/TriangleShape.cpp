#include "TriangleShape.h"

TriangleShape::TriangleShape(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
{
    glm::vec3 u = b - a;
    glm::vec3 v = c - a;
    m_normal = glm::normalize(glm::cross(u, v));
}

bool TriangleShape::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    float t = -glm::dot(rayOrigin, m_normal) / glm::dot(rayDirection, m_normal);
    hitPoint = rayOrigin + rayDirection * t;

    glm::vec3 u = m_b - m_a;
    glm::vec3 v = m_c - m_b;
    glm::vec3 w = m_a - m_c;

    glm::vec3 pA = hitPoint - m_a;
    glm::vec3 normalA = glm::cross(u, pA);

    glm::vec3 pB = hitPoint - m_b;
    glm::vec3 normalB = glm::cross(v, pB);

    glm::vec3 pC = hitPoint - m_c;
    glm::vec3 normalC = glm::cross(w, pC);

    if (std::copysign(1.0f, normalA.z) == std::copysign(1.0f, normalB.z) == std::copysign(1.0f, normalC.z))
    {
        hitNormal = normalA;
        return true;
    }

    return false;
}