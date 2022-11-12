#include "Material.h"
#include <GL/glew.h>

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
    Texture texture{ textureData, width, height, channelCount, textureSlot, 0 };
    glGenTextures(1, &texture.m_textureId);
    glBindTexture(GL_TEXTURE_2D, texture.m_textureId);
    int format = (channelCount == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    m_textureUniforms[uniformName] = texture;
}

const std::unordered_map<std::string, Texture>& Material::GetTextureUniforms()
{
    return m_textureUniforms;
}