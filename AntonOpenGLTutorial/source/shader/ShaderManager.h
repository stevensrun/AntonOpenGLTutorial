#pragma once

#include <string>
#include <unordered_map>

class ShaderProgram;

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager() = default;

    bool UseShader(const std::string& shaderName);
    bool LoadShader(const std::string& shaderName, const std::string& filepath);
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, float* value);
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, int* value);
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, unsigned int* value);
    void SetUniform(const std::string& shaderName, const std::string& uniformName, int size, bool transpose, float* value);

private:
    int GetUniformLocation(const std::string& uniformName);

private:
    ShaderProgram* m_activeShader;
    std::unordered_map<std::string, ShaderProgram*> m_shaders;
    std::unordered_map<ShaderProgram*, std::unordered_map<std::string, int>> m_shaderUniforms;
};