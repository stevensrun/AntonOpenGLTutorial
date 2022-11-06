#include "Material.h"

Material::Material(const std::string& shaderName)
    : m_shaderName(shaderName)
{
    m_ambientReflectivity = glm::vec3(1.0f);
    m_diffuseReflectivity = glm::vec3(1.0f);
    m_specularReflectivity = glm::vec4(1.0f);
}

const std::string& Material::GetShaderName() const
{
    return m_shaderName;
}