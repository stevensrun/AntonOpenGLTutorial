#include "Line.h"

Line::Line(const glm::vec3& p0, const glm::vec3 p1)
{
    AddAttribute(p0, p0);
    AddAttribute(p1, p0);
    FinalizeGeometry();
}

void Line::Draw(ShaderManager* shaderManager, Camera* camera, Light* light)
{
    PrepareShader(m_material, shaderManager, camera, light);
    glBindVertexArray(m_attributeVertexArray);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_points.size()));
}