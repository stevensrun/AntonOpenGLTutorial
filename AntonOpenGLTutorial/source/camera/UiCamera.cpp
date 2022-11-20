#include "UiCamera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

UiCamera::UiCamera(int width, int height)
    : Camera(glm::vec3(0.0f, 0.0f, 0.0f))
{
    m_view = glm::lookAt(m_position, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    float aspectRatio = static_cast<float>(width) / height;
    m_projection = glm::ortho(-1.0f, 1.0f, -aspectRatio / 2.0f, aspectRatio / 2.0f, -100.0f, 100.0f);
}