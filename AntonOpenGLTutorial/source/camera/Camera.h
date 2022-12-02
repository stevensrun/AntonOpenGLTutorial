#pragma once

#include <glm/glm.hpp>
#include "math/Quaternion.h"

class Camera
{
public:
    explicit Camera(const glm::vec3& position) noexcept;
    Camera(const Camera& rhs) = delete;
    virtual ~Camera() = 0;

    Camera& operator=(Camera& rhs) = delete;

    void SetAllowCameraMovement(bool allowed) noexcept;
    glm::vec3 GetPosition() const noexcept;
    glm::mat4 GetView() const noexcept;
    glm::mat4 GetProjection() const noexcept;
    Quaternion GetRotation() const noexcept;
    virtual void Update(float deltaTimeInSeconds) noexcept;

protected:
    const Quaternion m_forward;
    const Quaternion m_right;
    const Quaternion m_up;

    bool m_allowCameraMovement;
    glm::vec3 m_position;
    Quaternion m_rotation;
    glm::mat4 m_view;
    glm::mat4 m_projection;
};