#include "Triangle.h"

float Triangle::GetIntersectionParameter(const glm::vec3 rayOrigin, const glm::vec3& rayDirection)
{
    float t = -1.0f;
    float denominator = glm::dot(rayDirection, m_normal);

    if (denominator == 0.0f)
    {
        return t;
    }

    t = glm::dot(rayOrigin, m_normal) / denominator;

    return t;
}

void Triangle::AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute)
{
    Mesh::AddAttribute(point, color, lastAttribute);

    if (!lastAttribute)
    {
        return;
    }

    glm::vec3 a(m_positions[0].x, m_positions[0].y, m_positions[0].z);
    glm::vec3 b(m_positions[1].x, m_positions[1].y, m_positions[1].z);
    m_normal = glm::cross(a, b);
}

void Triangle::Draw()
{
    if (!m_enabled)
    {
        return;
    }

    glBindVertexArray(m_vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}