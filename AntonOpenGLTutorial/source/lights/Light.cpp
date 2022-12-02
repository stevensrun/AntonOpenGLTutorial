#include "Light.h"

Light::Light(const glm::vec3& position) noexcept
    : m_position(position)
    , m_ambientColor(1.0f)
    , m_diffuseColor(1.0f)
    , m_specularColor(1.0f)
{
}
