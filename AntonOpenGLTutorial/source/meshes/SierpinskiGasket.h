#pragma once

#include "Mesh.h"

class SierpinskiGasket : public BasicMesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    SierpinskiGasket(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int pointCount);
    virtual ~SierpinskiGasket() = default;

    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const;
};