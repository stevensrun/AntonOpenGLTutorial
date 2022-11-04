#include "Camera.h"

#include <glm/ext.hpp>

Camera::Camera(const glm::vec3 position)
    : m_position(position)
    , m_moveSpeedInSeconds(1.0f)
    , m_rotationSpeedInDegreesPerSecond(45.0f)
{
    m_rotation = Quaternion::AngleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_view = glm::lookAt(m_position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_projection = glm::perspective(glm::radians(67.0f), 1280.0f / 760.0f, 0.1f, 100.0f);
}

void Camera::Update()
{
    m_view = glm::lookAt(m_position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}