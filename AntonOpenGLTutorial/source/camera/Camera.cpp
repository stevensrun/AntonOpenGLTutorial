#include "Camera.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Camera::Camera(const glm::vec3& position)
    : m_position(position)
    , m_forward(0.0f, 0.0f, 0.0f, -1.0f)
    , m_right(0.0f, 1.0f, 0.0f, 0.0f)
    , m_up(0.0f, 0.0f, 1.0f, 0.0f)
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

Quaternion Camera::GetRotation() const
{
    return m_rotation;
}

void Camera::Update(float deltaTimeInSeconds)
{
}