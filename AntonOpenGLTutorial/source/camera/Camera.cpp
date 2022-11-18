#include "Camera.h"
#include <algorithm>
#include <glm/ext.hpp>

Camera::Camera(const glm::vec3 position)
    : m_position(position)
    , m_forward(Quaternion(0.0f, 0.0f, 0.0f, -1.0f))
    , m_right(Quaternion(0.0f, 1.0f, 0.0f, 0.0f))
    , m_up(Quaternion(0.0f, 0.0f, 1.0f, 0.0f))
    , m_velocity(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_currentYawInDegrees(0.0f)
    , m_currentPitchInDegrees(0.0f)
    , m_moveSpeedInSeconds(4.0f)
{
    m_rotation = Quaternion::AngleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_view = glm::lookAt(m_position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_projection = glm::perspective(glm::radians(67.0f), 1280.0f / 760.0f, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

glm::mat4 Camera::GetView() const
{
    return m_view;
}

glm::mat4 Camera::GetProjection() const
{
    return m_projection;
}

void Camera::MoveForward()
{
    Quaternion inverse = m_rotation.GetInverse();
    Quaternion forward = inverse * m_forward * m_rotation;
    m_velocity += glm::vec3(forward.x, forward.y, forward.z) * m_moveSpeedInSeconds;
}

void Camera::MoveBackward()
{
    Quaternion inverse = m_rotation.GetInverse();
    Quaternion forward = inverse * m_forward * m_rotation;
    m_velocity += glm::vec3(-forward.x, -forward.y, -forward.z) * m_moveSpeedInSeconds;
}

void Camera::MoveLeft()
{
    Quaternion inverse = m_rotation.GetInverse();
    Quaternion right = inverse * m_right * m_rotation;
    m_velocity += glm::vec3(-right.x, -right.y, -right.z) * m_moveSpeedInSeconds;
}

void Camera::MoveRight()
{
    Quaternion inverse = m_rotation.GetInverse();
    Quaternion right = inverse * m_right * m_rotation;
    m_velocity += glm::vec3(right.x, right.y, right.z) * m_moveSpeedInSeconds;
}

void Camera::MoveUp()
{
    Quaternion inverse = m_rotation.GetInverse();
    Quaternion up = inverse * m_up * m_rotation;
    m_velocity += glm::vec3(up.x, up.y, up.z) * m_moveSpeedInSeconds;
}

void Camera::MoveDown()
{
    Quaternion inverse = m_rotation.GetInverse();
    Quaternion up = inverse * m_up * m_rotation;
    m_velocity += glm::vec3(-up.x, -up.y, -up.z) * m_moveSpeedInSeconds;
}

void Camera::Yaw(float angleInDegrees)
{
    m_currentYawInDegrees += angleInDegrees * 0.25f;
}

void Camera::Pitch(float angleInDegrees)
{
    m_currentPitchInDegrees += angleInDegrees * 0.25f;
}

void Camera::Update(float deltaTimeInSeconds)
{
    m_rotation = Quaternion::FromEulerAngles(0.0f, -m_currentPitchInDegrees, -m_currentYawInDegrees);

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion forward = inverse * m_forward * m_rotation;
    Quaternion up = inverse * m_up * m_rotation;

    if (glm::length(m_velocity) != 0.0f)
    {
        m_velocity = glm::normalize(m_velocity) * m_moveSpeedInSeconds * deltaTimeInSeconds;
    }

    m_position += m_velocity;
    m_view = glm::lookAt(m_position, m_position + glm::vec3(forward.x, forward.y, forward.z), glm::vec3(up.x, up.y, up.z));
    m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}