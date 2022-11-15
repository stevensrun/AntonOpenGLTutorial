#include "TriangleShape.h"
#include <algorithm>

TriangleShape::TriangleShape(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
    glm::vec3 u = b - a;
    glm::vec3 v = c - a;
    glm::vec3 normal = glm::normalize(glm::cross(u, v));
    AddAttribute(a, normal);
    AddAttribute(b, normal);
    AddAttribute(c, normal);
    FinalizeGeometry();
}

bool TriangleShape::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface)
{
    glm::vec3 normal = m_normals[0];
    float denominator = glm::dot(rayDirection, normal);;

    if (!allowBackface && denominator >= 0.0f || allowBackface && abs(denominator) <= 0.0001f)
    {
        return false;
    }

    glm::vec3 a = m_points[0];
    glm::vec3 b = m_points[1];
    glm::vec3 c = m_points[2];
    float d = -glm::dot(normal, a);
    float t = (-glm::dot(rayOrigin, normal) - d) / denominator;

    if (t <= 0.0f)
    {
        return false;
    }

    hitPoint = rayOrigin + rayDirection * t;
    hitNormal = normal;

    glm::vec3 u = b - a;
    glm::vec3 v = c - b;
    glm::vec3 w = a - c;
    glm::vec3 pA = hitPoint - a;
    glm::vec3 normalA = glm::normalize(glm::cross(u, pA));
    glm::vec3 pB = hitPoint - b;
    glm::vec3 normalB = glm::normalize(glm::cross(v, pB));
    glm::vec3 pC = hitPoint - c;
    glm::vec3 normalC = glm::normalize(glm::cross(w, pC));
    float dotA = std::clamp(glm::dot(normalA, normal), -1.0f, 1.0f);
    float dotB = std::clamp(glm::dot(normalB, normal),-1.0f, 1.0f);
    float dotC = std::clamp(glm::dot(normalC, normal), -1.0f, 1.0f);

    if (abs(dotA - dotB) <= 0.001f && abs(dotB - dotC) <= 0.001f)
    {
        return true;
    }

    return false;
}

void TriangleShape::Draw(ShaderManager* shaderManager) const
{
    if (!m_enabled)
    {
        return;
    }

    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glLineWidth(1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
}