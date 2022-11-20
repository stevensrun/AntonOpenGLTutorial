#pragma once

#include "Camera.h"

class SceneCamera : public Camera
{
public:
    SceneCamera(const glm::vec3 position, float verticalFieldOfViewInDegrees, float aspectRatio);
    virtual ~SceneCamera() = default;

    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void Yaw(float angleInDegrees);
    void Pitch(float angleInDegrees);
    virtual void Update(float deltaTimeInSeconds) override;

protected:
    glm::vec3 m_velocity;
    float m_currentYawInDegrees;
    float m_currentPitchInDegrees;
    float m_moveSpeedInSeconds;
};