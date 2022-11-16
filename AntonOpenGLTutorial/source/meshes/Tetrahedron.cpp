#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(int subdivisionCount, bool useVertexNormals)
    : m_useVertexNormals(useVertexNormals)
{
    glm::vec3 a(0.0f, 0.9f, -0.333f);
    glm::vec3 b(0.0f, 0.0f, 1.0f);
    glm::vec3 c(0.816f, -0.471f, -0.333f);
    glm::vec3 d(-0.816f, -0.471f, -0.333f);

    divideTriangle(a, b, c, subdivisionCount);
    divideTriangle(a, d, b, subdivisionCount);
    divideTriangle(b, d, c, subdivisionCount);
    divideTriangle(a, c, d, subdivisionCount);
    FinalizeGeometry();
}

void Tetrahedron::divideTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int recursiveCount)
{
    if (recursiveCount == 0)
    {
        if (m_useVertexNormals)
        {
            AddAttribute(a, a);
            AddAttribute(b, b);
            AddAttribute(c, c);
        }
        else
        {
            glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
        }
    }
    else
    {
        glm::vec3 u = glm::normalize((a + b) / 2.0f);
        glm::vec3 v = glm::normalize((b + c) / 2.0f);
        glm::vec3 w = glm::normalize((c + a) / 2.0f);
        divideTriangle(a, u, w, recursiveCount - 1);
        divideTriangle(b, v, u, recursiveCount - 1);
        divideTriangle(c, w, v, recursiveCount - 1);
        divideTriangle(u, v, w, recursiveCount - 1);
    }
}