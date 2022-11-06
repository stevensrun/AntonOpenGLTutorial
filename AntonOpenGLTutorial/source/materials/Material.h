#pragma once

#include <glm/glm.hpp>
#include <string>

class Material
{
public:
    explicit Material(const std::string& shaderName);
    ~Material() = default;

    const std::string& GetShaderName() const;

public:
    glm::vec3 m_ambientReflectivity;
    glm::vec3 m_diffuseReflectivity;
    glm::vec4 m_specularReflectivity;

protected:
    std::string m_shaderName;
};