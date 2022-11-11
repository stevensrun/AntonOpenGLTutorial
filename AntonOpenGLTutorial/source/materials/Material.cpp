#include "Material.h"

Material::Material(const std::string& shaderName)
    : m_shaderName(shaderName)
    , m_baseTextureData(nullptr)
    , m_textureWidth(0)
    , m_textureHeight(0)
    , m_textureChannelCount(0)
    , m_baseTextureSlot(-1)
{
    m_ambientReflectivity = glm::vec3(1.0f);
    m_diffuseReflectivity = glm::vec3(1.0f);
    m_specularReflectivity = glm::vec4(1.0f);
}

const std::string& Material::GetShaderName() const
{
    return m_shaderName;
}

void Material::SetBaseTexture(unsigned char* textureData, int width, int height, int channelCount, int textureSlot)
{
    m_baseTextureData = textureData;
    m_textureWidth = width;
    m_textureHeight = height;
    m_textureChannelCount = channelCount;
    m_baseTextureSlot = textureSlot;
}

const unsigned char* Material::GetBaseTextureData() const
{
    return m_baseTextureData;
}

int Material::GetTextureWidth() const
{
    return m_textureWidth;
}

int Material::GetTextureHeight() const
{
    return m_textureHeight;
}

int Material::GetTextureChannelCount() const
{
    return m_textureChannelCount;
}

int Material::GetTextureSlot() const
{
    return m_baseTextureSlot;
}