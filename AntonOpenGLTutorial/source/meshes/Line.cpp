#include "Line.h"
#include <GL/glew.h>

Line::Line(const glm::vec3& p0, const glm::vec3 p1)
{
    AddAttribute(p0);
    AddAttribute(p1);
    FinalizeGeometry();
}

void Line::Draw(ShaderManager* shaderManager) const
{
    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glLineWidth(6.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_points.size()));
}