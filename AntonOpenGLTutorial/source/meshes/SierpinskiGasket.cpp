#include "SierpinskiGasket.h"
#include <GL/glew.h>
#include <vector>

SierpinskiGasket::SierpinskiGasket(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int pointCount)
{
    std::vector<glm::vec3> vertices{ a, b, c};
    
    glm::vec3 p(0.25f, 0.5f, 0.0f);
    AddAttribute(p);

    for (int i = 1; i < pointCount; i++)
    {
        int j = rand() % 3;
        p = (p + vertices[j]) / 2.0f;
        AddAttribute(p);
    }

    FinalizeGeometry();
}

void SierpinskiGasket::Draw(std::shared_ptr<ShaderManager>& shaderManager) const
{
    if (!m_material)
    {
        return;
    }

    glBindVertexArray(m_attributeVertexArray);
    PrepareShader(m_material, shaderManager);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_POINTS, 0, static_cast<int>(m_points.size()));
}
