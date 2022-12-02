#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include "textures/TextureManager.h"
#include <unordered_map>
#include <vector>

class ShaderManager;
class Texture;

class Material
{
public:
    explicit Material(const std::string& shaderName) noexcept;
    virtual ~Material() = default;

    const std::string& GetShaderName() const noexcept;
    void AddTextureUniform(const std::string& uniformName, const std::string& textureFilepath) noexcept;
    void AddUniform(const std::string& uniformName, const glm::vec3& value) noexcept;
    void AddUniform(const std::string& uniformName, const glm::vec4& value) noexcept;
    const std::unordered_map<std::string, std::pair<std::shared_ptr<Texture>, unsigned int>>& GetTextureUniforms() noexcept;
    const std::unordered_map<std::string, glm::vec3>& GetVec3Uniforms() noexcept;
    const std::unordered_map<std::string, glm::vec4>& GetVec4Uniforms() noexcept;

protected:
    static TextureManager s_textureManager;

    std::string m_shaderName;
    std::unordered_map<std::string, std::pair<std::shared_ptr<Texture>, unsigned int>> m_textureUniforms;
    std::unordered_map<std::string, glm::vec3> m_vec3Uniforms;
    std::unordered_map<std::string, glm::vec4> m_vec4Uniforms;
};