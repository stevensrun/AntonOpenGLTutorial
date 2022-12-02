#pragma once

#include <memory>
#include <string>

class Shader;

class ShaderProgram final
{
public:
    explicit ShaderProgram(const std::string& filepath) noexcept;
    ~ShaderProgram();

    bool IsValid() const noexcept;
    unsigned int GetId() const noexcept;
    void Bind() const noexcept;
    void Unbind() const noexcept;

private:
    unsigned int m_id;
    std::unique_ptr<Shader> m_vertexShader;
    std::unique_ptr<Shader> m_fragmentShader;
};