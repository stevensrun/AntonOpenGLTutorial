#include "SceneCamera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

SceneCamera::SceneCamera(const glm::vec3 position, float verticalFieldOfViewInDegrees, float aspectRatio) noexcept
    : Camera(position)
    , m_velocity(0.0f, 0.0f, 0.0f)
    , m_currentYawInDegrees(0.0f)
    , m_currentPitchInDegrees(0.0f)
    , m_moveSpeedInSeconds(4.0f)
{
    m_rotation = Quaternion::AngleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_projection = glm::perspective(glm::radians(verticalFieldOfViewInDegrees), aspectRatio, 0.1f, 100.0f);
    Update(0.0f);
}

void SceneCamera::MoveForward() noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion forward = inverse * m_forward * m_rotation;
    m_velocity += glm::vec3(forward.x, forward.y, forward.z) * m_moveSpeedInSeconds;
}

void SceneCamera::MoveBackward() noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion forward = inverse * m_forward * m_rotation;
    m_velocity += glm::vec3(-forward.x, -forward.y, -forward.z) * m_moveSpeedInSeconds;
}

void SceneCamera::MoveLeft() noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion right = inverse * m_right * m_rotation;
    m_velocity += glm::vec3(-right.x, -right.y, -right.z) * m_moveSpeedInSeconds;
}

void SceneCamera::MoveRight() noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion right = inverse * m_right * m_rotation;
    m_velocity += glm::vec3(right.x, right.y, right.z) * m_moveSpeedInSeconds;
}

void SceneCamera::MoveUp() noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion up = inverse * m_up * m_rotation;
    m_velocity += glm::vec3(up.x, up.y, up.z) * m_moveSpeedInSeconds;
}

void SceneCamera::MoveDown() noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    Quaternion inverse = m_rotation.GetInverse();
    Quaternion up = inverse * m_up * m_rotation;
    m_velocity += glm::vec3(-up.x, -up.y, -up.z) * m_moveSpeedInSeconds;
}

void SceneCamera::Yaw(float angleInDegrees) noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    m_currentYawInDegrees += angleInDegrees * 0.25f;
}

void SceneCamera::Pitch(float angleInDegrees) noexcept
{
    if (!m_allowCameraMovement)
    {
        return;
    }

    m_currentPitchInDegrees += angleInDegrees * 0.25f;
}

void SceneCamera::Update(float deltaTimeInSeconds) noexcept
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