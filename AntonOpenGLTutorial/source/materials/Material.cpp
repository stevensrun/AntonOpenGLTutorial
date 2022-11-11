#include "Material.h"

Material::Material(const std::string& shaderName)
    : m_shaderName(shaderName)
{
}

const std::string& Material::GetShaderName() const
{
    return m_shaderName;
}

void Material::AddUniform(const std::string& uniformName, const glm::vec3& value)
{
    m_vec3Uniforms[uniformName] = value;
}

void Material::AddUniform(const std::string& uniformName, const glm::vec4& value)
{
    m_vec4Uniforms[uniformName] = value;
}

const std::unordered_map<std::string, glm::vec3>& Material::GetVec3Uniforms()
{
    return m_vec3Uniforms;
}

const std::unordered_map<std::string, glm::vec4>& Material::GetVec4Uniforms()
{
    return m_vec4Uniforms;
}

void Material::AddTextureUniform(const std::string& uniformName, unsigned char* textureData, int width, int height, int channelCount, int textureSlot)
{
    Texture texture{ textureData, width, height, channelCount, textureSlot };
    m_textureUniforms[uniformName] = texture;
}

const std::unordered_map<std::string, Texture>& Material::GetTextureUniforms()
{
    return m_textureUniforms;
}