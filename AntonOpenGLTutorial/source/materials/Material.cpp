#include "Material.h"
#include <GL/glew.h>
#include "textures/Texture.h"

TextureManager Material::s_textureManager;

Material::Material(const std::string& shaderName) noexcept
    : m_shaderName(shaderName)
{
}

const std::string& Material::GetShaderName() const noexcept
{
    return m_shaderName;
}

void Material::AddTextureUniform(const std::string& uniformName, const std::string& textureFilepath) noexcept
{
    std::shared_ptr<Texture> texture = Material::s_textureManager.GetTexture(textureFilepath);

    if (!texture)
    {
        return;
    }

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, texture->GetFormat(), texture->GetWidth(), texture->GetHeight(), 0, texture->GetFormat(), GL_UNSIGNED_BYTE, texture->GetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    m_textureUniforms[uniformName] = std::make_pair(texture, textureId);
}

void Material::AddUniform(const std::string& uniformName, const glm::vec3& value) noexcept
{
    m_vec3Uniforms[uniformName] = value;
}

void Material::AddUniform(const std::string& uniformName, const glm::vec4& value) noexcept
{
    m_vec4Uniforms[uniformName] = value;
}

const std::unordered_map<std::string, std::pair<std::shared_ptr<Texture>, unsigned int>>& Material::GetTextureUniforms() noexcept
{
    return m_textureUniforms;
}

const std::unordered_map<std::string, glm::vec3>& Material::GetVec3Uniforms() noexcept
{
    return m_vec3Uniforms;
}

const std::unordered_map<std::string, glm::vec4>& Material::GetVec4Uniforms() noexcept
{
    return m_vec4Uniforms;
}