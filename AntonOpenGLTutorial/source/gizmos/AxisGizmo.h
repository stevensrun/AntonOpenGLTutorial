#pragma once

#include "Gizmo.h"

class SceneCamera;

class AxisGizmo final : public Gizmo
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    AxisGizmo();
    virtual ~AxisGizmo() = default;

    virtual void AddAttribute(const glm::vec3& point);
    virtual void AddAttribute(const glm::vec3& point, const glm::vec4& color);
    virtual void Update(float deltaTimeInSeconds, std::shared_ptr<SceneCamera>& camera) noexcept override;
    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const;
};