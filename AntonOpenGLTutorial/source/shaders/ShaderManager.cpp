#include "ShaderManager.h"

#include <cassert>
#include <GL/glew.h>
#include "ShaderProgram.h"

bool ShaderManager::UseShader(const std::string& shaderName) noexcept
{
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>>::const_iterator it = m_shaders.find(shaderName);

    if (it == m_shaders.end())
    {
        glUseProgram(0);
        return false;
    }

    if (it->second == m_activeShader)
    {
        return true;
    }

    m_activeShader = it->second;
    glUseProgram(m_activeShader->GetId());
    return true;
}

bool ShaderManager::LoadShader(const std::string& shaderName, const std::string& filepath) noexcept
{
    std::shared_ptr<ShaderProgram> program = std::make_shared<ShaderProgram>(filepath);

    if (!program->IsValid())
    {
        return false;
    }

    m_shaders[shaderName] = program;
    return true;
}

void ShaderManager::SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, float* value) noexcept
{
    if (!UseShader(shaderName))
    {
        return;
    }

    int location = GetUniformLocation(uniformName);

    if (location == -1)
    {
        return;
    }

    switch (stride)
    {
    case 1:
        glUniform1fv(location, 1, value);
        break;

    case 2:
        glUniform2fv(location, 1, value);
        break;

    case 3:
        glUniform3fv(location, 1, value);
        break;

    case 4:
        glUniform4fv(location, 1, value);
        break;
    }
}

void ShaderManager::SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, int* value) noexcept
{
    if (!UseShader(shaderName))
    {
        return;
    }

    int location = GetUniformLocation(uniformName);

    if (location == -1)
    {
        return;
    }

    switch (stride)
    {
    case 1:
        glUniform1iv(location, 1, value);
        break;

    case 2:
        glUniform2iv(location, 1, value);
        break;

    case 3:
        glUniform3iv(location, 1, value);
        break;

    case 4:
        glUniform4iv(location, 1, value);
        break;
    }

}

void ShaderManager::SetUniform(const std::string& shaderName, const std::string& uniformName, int stride, unsigned int* value) noexcept
{
    if (!UseShader(shaderName))
    {
        return;
    }

    int location = GetUniformLocation(uniformName);

    if (location == -1)
    {
        return;
    }

    switch (stride)
    {
    case 1:
        glUniform1uiv(location, 1, value);
        break;

    case 2:
        glUniform2uiv(location, 1, value);
        break;

    case 3:
        glUniform3uiv(location, 1, value);
        break;

    case 4:
        glUniform4uiv(location, 1, value);
        break;
    }

}

void ShaderManager::SetUniform(const std::string& shaderName, const std::string& uniformName, int rows, int columns, bool transpose, float* value) noexcept
{
    if (!UseShader(shaderName))
    {
        return;
    }

    int location = GetUniformLocation(uniformName);

    if (location == -1)
    {
        return;
    }

    assert(rows == columns);

    switch (rows)
    {
    case 2:
        glUniformMatrix2fv(location, 1, transpose, value);
        break;

    case 3:
        glUniformMatrix3fv(location, 1, transpose, value);
        break;

    case 4:
        glUniformMatrix4fv(location, 1, transpose, value);
        break;
    }

}

int ShaderManager::GetUniformLocation(const std::string& uniformName) noexcept
{
    if (m_shaderUniforms.find(m_activeShader) == m_shaderUniforms.end())
    {
        m_shaderUniforms[m_activeShader] = std::unordered_map<std::string, int>();
    }

    std::unordered_map<std::string, int> uniformLocations = m_shaderUniforms[m_activeShader];

    if (uniformLocations.find(uniformName) == uniformLocations.end())
    {
        int location = glGetUniformLocation(m_activeShader->GetId(), uniformName.c_str());
        uniformLocations[uniformName] = location;
    }

    return uniformLocations[uniformName];
}