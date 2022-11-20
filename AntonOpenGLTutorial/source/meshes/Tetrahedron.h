#pragma once

#include "Mesh.h"

class Tetrahedron : public Mesh
{
public:
    Tetrahedron(int subdivisionCount, bool useVertexNormals);
    virtual ~Tetrahedron() = default;

private:
    void divideTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int recusiveCount);

private:
    bool m_useVertexNormals;
    int m_firstElementIndex;
};