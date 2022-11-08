#include "Dot.h"

Dot::Dot()
{
    m_enabled = false;
    AddAttribute(glm::vec4(0.0f, 0.0f, 0.1f, 1.0f), glm::vec3(0.0, 0.0, 1.0f));
    FinalizeGeometry();
}

bool Dot::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    return false;
}

void Dot::Draw(ShaderManager* shaderManager, Camera* camera, Light* light)
{
    if (!m_enabled)
    {
        return;
    }


    PrepareShader(m_material, shaderManager, camera, light);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}
