#include "Camera.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Camera::Camera(const glm::vec3& position) noexcept
    : m_forward(0.0f, 0.0f, 0.0f, -1.0f)
    , m_right(0.0f, 1.0f, 0.0f, 0.0f)
    , m_up(0.0f, 0.0f, 1.0f, 0.0f)
    , m_allowCameraMovement(false)
    , m_position(position)
    , m_rotation(Quaternion::AngleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)))
    , m_view(1.0f)
    , m_projection(1.0f)
{
}

Camera::~Camera()
{
}

void Camera::SetAllowCameraMovement(bool allowed) noexcept
{
    m_allowCameraMovement = allowed;
}

glm::vec3 Camera::GetPosition() const noexcept
{
    return m_position;
}

glm::mat4 Camera::GetView() const noexcept
{
    return m_view;
}

glm::mat4 Camera::GetProjection() const noexcept
{
    return m_projection;
}

Quaternion Camera::GetRotation() const noexcept
{
    return m_rotation;
}

void Camera::Update(float deltaTimeInSeconds) noexcept
{
}