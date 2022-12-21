#include "Dot.h"
#include <GL/glew.h>

Dot::Dot()
{
    m_enabled = false;
    AddAttribute(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    FinalizeGeometry();
}
void Dot::AddAttribute(const glm::vec3& point, const glm::vec3& normal)
{
    glDeleteBuffers(1, &m_attributesBuffer);
    glDeleteBuffers(1, &m_normalsBuffer);

    m_points.clear();
    m_normals.clear();
    m_points.push_back(point);
    m_normals.push_back(normal);
    FinalizeGeometry();
}

void Dot::Draw(std::shared_ptr<ShaderManager>& shaderManager) const
{
    if (!m_enabled)
    {
        return;
    }

    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glPointSize(1.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}