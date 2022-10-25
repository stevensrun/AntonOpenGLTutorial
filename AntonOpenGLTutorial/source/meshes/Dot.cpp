#include "Dot.h"

float Dot::GetIntersectionParameter(const glm::vec3 rayOrigin, const glm::vec3& rayDirection)
{
    return -1.0f;
}

void Dot::Draw()
{
    if (!m_enabled)
    {
        return;
    }

    glPointSize(0.5);
    glDrawArrays(GL_POINTS, 0, 1);
}
