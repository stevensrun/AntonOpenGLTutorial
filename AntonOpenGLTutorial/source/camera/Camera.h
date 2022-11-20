#pragma once

#include <glm/glm.hpp>
#include "math/Quaternion.h"

class Camera
{
public:
    explicit Camera(const glm::vec3& position);
    virtual ~Camera() = default;

    glm::vec3 GetPosition() const;
    glm::mat4 GetView() const;
    glm::mat4 GetProjection() const;
    Quaternion GetRotation() const;
    virtual void Update(float deltaTimeInSeconds);

protected:
    const Quaternion m_forward;
    const Quaternion m_right;
    const Quaternion m_up;

    glm::vec3 m_position;
    Quaternion m_rotation;
    glm::mat4 m_view;
    glm::mat4 m_projection;
};