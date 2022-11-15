#include "Line.h"

Line::Line(const glm::vec3& p0, const glm::vec3 p1)
{
    AddAttribute(p0, p0);
    AddAttribute(p1, p0);
    FinalizeGeometry();
}

bool Line::HitTest(TriangleShape*& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface) const
{
    return false;
}

void Line::Draw(ShaderManager* shaderManager) const
{
    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glLineWidth(6.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_points.size()));
}