#pragma once

#include "Mesh.h"

class Tetrahedron : public Mesh
{
public:
    explicit Tetrahedron(int subdivisionCount);
    virtual ~Tetrahedron() = default;

private:
    void divideTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int recusiveCount);
};