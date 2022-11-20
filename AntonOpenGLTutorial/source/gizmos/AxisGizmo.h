#pragma once

#include "Gizmo.h"

class SceneCamera;

class AxisGizmo : public Gizmo
{
public:
    AxisGizmo();
    virtual ~AxisGizmo() = default;

    virtual void AddAttribute(const glm::vec3& point);
    virtual void AddAttribute(const glm::vec3& point, const glm::vec4& color);
    virtual void Update(float deltaTimeInSeconds, SceneCamera* camera) override;
    virtual void Draw(ShaderManager* shaderManager) const;
};