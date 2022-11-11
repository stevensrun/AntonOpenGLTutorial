#pragma once

#include <glm/glm.hpp>
#include <string>

class ShaderManager;

class Material
{
public:
    explicit Material(const std::string& shaderName);
    virtual ~Material() = default;

    const std::string& GetShaderName() const;
    void SetBaseTexture(unsigned char* textureData, int width, int height, int channelCount, int textureSlot);
    const unsigned char* GetBaseTextureData() const;
    int GetTextureWidth() const;
    int GetTextureHeight() const;
    int GetTextureChannelCount() const;
    int GetTextureSlot() const;

public:
    glm::vec3 m_ambientReflectivity;
    glm::vec3 m_diffuseReflectivity;
    glm::vec4 m_specularReflectivity;

protected:
    std::string m_shaderName;
    unsigned char* m_baseTextureData;
    int m_textureWidth;
    int m_textureHeight;
    int m_textureChannelCount;
    int m_baseTextureSlot;
};