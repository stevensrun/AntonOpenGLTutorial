#pragma once

#include "Mesh.h"

class Tetrahedron : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Tetrahedron(int subdivisionCount, bool useVertexNormals);
    virtual ~Tetrahedron() = default;

private:
    void divideTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int recusiveCount);

private:
    bool m_useVertexNormals;
    int m_firstElementIndex;
};