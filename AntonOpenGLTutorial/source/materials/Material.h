#pragma once

#include <glm/glm.hpp>
#include <string>
#include "textures/TextureManager.h"
#include <unordered_map>
#include <vector>

class ShaderManager;
class Texture;

class Material
{
public:
    explicit Material(const std::string& shaderName);
    virtual ~Material() = default;

    const std::string& GetShaderName() const;
    void AddTextureUniform(const std::string& uniformName, const std::string& textureFilepath);
    void AddUniform(const std::string& uniformName, const glm::vec3& value);
    void AddUniform(const std::string& uniformName, const glm::vec4& value);
    const std::unordered_map<std::string, std::pair<Texture*, unsigned int>>& GetTextureUniforms();
    const std::unordered_map<std::string, glm::vec3>& GetVec3Uniforms();
    const std::unordered_map<std::string, glm::vec4>& GetVec4Uniforms();

protected:
    static TextureManager s_textureManager;

    std::string m_shaderName;
    std::unordered_map<std::string, std::pair<Texture*, unsigned int>> m_textureUniforms;
    std::unordered_map<std::string, glm::vec3> m_vec3Uniforms;
    std::unordered_map<std::string, glm::vec4> m_vec4Uniforms;
};