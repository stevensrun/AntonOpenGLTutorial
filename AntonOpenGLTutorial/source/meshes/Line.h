#pragma once

#include "Mesh.h"

class Line : public BasicMesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Line(const glm::vec3& p0, const glm::vec3 p1);
    virtual ~Line() = default;

    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const override;
};