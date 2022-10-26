#include "Dot.h"

Dot::Dot()
{
    m_enabled = false;
}

bool Dot::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    return false;
}

void Dot::Draw()
{
    if (!m_enabled)
    {
        return;
    }

    glBindVertexArray(m_vertexArray);
    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}
