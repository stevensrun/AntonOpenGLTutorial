#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class ShaderManager;

struct Texture
{
    unsigned char* m_data;
    int m_width;
    int m_height;
    int m_channelCount;
    int m_slot;
};

class Material
{
public:
    explicit Material(const std::string& shaderName);
    virtual ~Material() = default;

    const std::string& GetShaderName() const;
    void AddUniform(const std::string& uniformName, const glm::vec3& value);
    void AddUniform(const std::string& uniformName, const glm::vec4& value);
    const std::unordered_map<std::string, glm::vec3>& GetVec3Uniforms();
    const std::unordered_map<std::string, glm::vec4>& GetVec4Uniforms();
    void AddTextureUniform(const std::string& uniformName, unsigned char* textureData, int width, int height, int channelCount, int textureSlot);
    const std::unordered_map<std::string, Texture>& GetTextureUniforms();

protected:
    std::string m_shaderName;
    std::unordered_map<std::string, glm::vec3> m_vec3Uniforms;
    std::unordered_map<std::string, glm::vec4> m_vec4Uniforms;
    std::unordered_map<std::string, Texture> m_textureUniforms;
};