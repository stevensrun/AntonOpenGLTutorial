#pragma once

#include <glm/glm.hpp>

class Light
{
public:
    explicit Light(const glm::vec3& position);
    virtual ~Light() = default;

public:
    glm::vec3 m_position;
    glm::vec3 m_ambientColor;
    glm::vec3 m_diffuseColor;
    glm::vec3 m_specularColor;
};