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
    float denominator = glm::dot(rayDirection, m_normal);

    if (abs(denominator) <= 0.001f)
    {
        return false;
    }

    float d = -glm::dot(m_normal, m_a);
    float t = (-glm::dot(rayOrigin, m_normal) - d) / denominator;

    if (t <= 0.0f)
    {
        return false;
    }

    hitPoint = rayOrigin + rayDirection * t;

    glm::vec3 u = m_b - m_a;
    glm::vec3 v = m_c - m_b;
    glm::vec3 w = m_a - m_c;
    glm::vec3 pA = hitPoint - m_a;
    glm::vec3 normalA = glm::normalize(glm::cross(u, pA));
    glm::vec3 pB = hitPoint - m_b;
    glm::vec3 normalB = glm::normalize(glm::cross(v, pB));
    glm::vec3 pC = hitPoint - m_c;
    glm::vec3 normalC = glm::normalize(glm::cross(w, pC));
    float dotAB = glm::dot(normalA, normalB);
    float dotAC = glm::dot(normalA, normalC);
    float dotBC = glm::dot(normalB, normalC);
    float diff = (dotAB - dotAC) - (dotAC - dotBC);

    if (abs(diff) <= 0.0001f) 
    {
        return true;
    }

    return false;
}