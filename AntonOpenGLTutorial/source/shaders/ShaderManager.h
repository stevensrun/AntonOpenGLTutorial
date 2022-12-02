#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class ShaderProgram;

class ShaderManager final
{
public:
    ShaderManager() noexcept = default;
    ~ShaderManager() = default;

    bool UseShader(const std::string& shaderName) noexcept;
    bool LoadShader(const std::string& shaderName, const std::string& filepath) noexcept;
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, float* value) noexcept;
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, int* value) noexcept;
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, unsigned int* value) noexcept;
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int rows, int columns, bool transpose, float* value) noexcept;

private:
    int GetUniformLocation(const std::string& uniformName) noexcept;

private:
    std::shared_ptr<ShaderProgram> m_activeShader;
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaders;
    std::unordered_map<std::shared_ptr<ShaderProgram>, std::unordered_map<std::string, int>> m_shaderUniforms;
};