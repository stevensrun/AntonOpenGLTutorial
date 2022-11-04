#pragma once

#include <glm/glm.hpp>
#include "math/Quaternion.h"

class Camera
{
public:
    explicit Camera(const glm::vec3 position);
    virtual ~Camera() = default;

    void Update();

public:
    glm::vec3 m_position;
    Quaternion m_rotation;
    float m_moveSpeedInSeconds;
    float m_rotationSpeedInDegreesPerSecond;
    glm::mat4 m_view;
    glm::mat4 m_projection;
};