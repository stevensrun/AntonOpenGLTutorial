#pragma once

#include <glm/glm.hpp>
#include "math/Quaternion.h"

class Camera
{
public:
    explicit Camera(const glm::vec3 position);
    virtual ~Camera() = default;

    glm::vec3 GetPosition() const;
    glm::mat4 GetView() const;
    glm::mat4 GetProjection() const;
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void Yaw(float angleInDegrees);
    void Pitch(float angleInDegrees);
    void Update(float deltaTimeInSeconds);

private:
    const Quaternion m_forward;
    const Quaternion m_right;
    const Quaternion m_up;

    glm::vec3 m_position;
    glm::mat4 m_view;
    glm::mat4 m_projection;
    Quaternion m_rotation;
    glm::vec3 m_velocity;
    float m_currentYawInDegrees;
    float m_currentPitchInDegrees;
    float m_moveSpeedInSeconds;
};