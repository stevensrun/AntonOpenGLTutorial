#include "Triangle.h"
#include <glm/ext.hpp>

Triangle::Triangle()
    : m_t(0.0f)
    , m_normal(0.0f, 0.0f, 0.0f)
{

}

bool Triangle::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    std::vector<glm::vec4> tempPoints = GetTransformedPoints();
    glm::vec3 point(tempPoints[0]);
    float t = glm::dot(point - rayOrigin, m_normal) / glm::dot(rayDirection, m_normal);
    hitPoint = rayOrigin + rayDirection * t;

    for (size_t i = 0; i < tempPoints.size(); i++)
    {
        const glm::vec3& tail = tempPoints[i];
        const glm::vec3& head = tempPoints[(i + 1) % tempPoints.size()];
        glm::vec3 u = head - tail;
        glm::vec3 v = hitPoint - tail;
        glm::vec3 w = glm::cross(u, v);
        float dotProduct = glm::dot(m_normal, w);

        if (dotProduct <= 0.0f)
        {
            return false;
        }
    }

    hitNormal = m_normal;

    return true;
}

void Triangle::AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute)
{
    Mesh::AddAttribute(point, color, lastAttribute);

    if (!lastAttribute)
    {
        return;
    }

    UpdateNormal();
}

void Triangle::Update(float deltaTimeInSeconds)
{
    m_t += 0.001f;
    Quaternion q = Quaternion::AngleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Quaternion r = Quaternion::AngleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_rotation = Quaternion::Slerp(q, r, m_t);
    UpdateNormal();
}

void Triangle::Draw()
{
    if (!m_enabled)
    {
        return;
    }

    std::vector<glm::vec4> tempPoints = GetTransformedPoints();
    glBindVertexArray(m_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_pointBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * tempPoints.size(), tempPoints.data());
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::UpdateNormal()
{
    std::vector<glm::vec4> tempPoints = GetTransformedPoints();
    glm::vec3 u = glm::vec3(tempPoints[1] - tempPoints[0]);
    glm::vec3 v = glm::vec3(tempPoints[2] - tempPoints[0]);
    m_normal = glm::normalize(glm::cross(u, v));
}

std::vector<glm::vec4> Triangle::GetTransformedPoints()
{
    std::vector<glm::vec4> tempPoints;
    glm::mat4 R = m_rotation.ToMatrix();
    glm::mat4 T = glm::translate(glm::mat4(1.0f), m_position);
    glm::mat4 transform = T * R;

    for (const glm::vec4& point : m_points)
    {
        glm::vec4 transformed = transform * point;
        tempPoints.push_back(transformed);
    }

    return tempPoints;
}