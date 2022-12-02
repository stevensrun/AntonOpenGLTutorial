#pragma once

#include "Camera.h"

class SceneCamera : public Camera
{
public:
    SceneCamera(const glm::vec3 position, float verticalFieldOfViewInDegrees, float aspectRatio) noexcept;
    virtual ~SceneCamera() = default;

    void MoveForward() noexcept;
    void MoveBackward() noexcept;
    void MoveLeft() noexcept;
    void MoveRight() noexcept;
    void MoveUp() noexcept;
    void MoveDown() noexcept;
    void Yaw(float angleInDegrees) noexcept;
    void Pitch(float angleInDegrees) noexcept;
    virtual void Update(float deltaTimeInSeconds) noexcept override;

protected:
    glm::vec3 m_velocity;
    float m_currentYawInDegrees;
    float m_currentPitchInDegrees;
    float m_moveSpeedInSeconds;
};