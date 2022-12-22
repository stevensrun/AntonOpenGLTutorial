#pragma once

#include "Mesh.h"

class Dot final : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Dot();
    virtual ~Dot() = default;

    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal) override;
    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const override;
};