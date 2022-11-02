#include "Triangle.h"
#include <glm/ext.hpp>

Triangle::Triangle()
    : m_t(0.0f)
{

}

bool Triangle::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    return false;
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