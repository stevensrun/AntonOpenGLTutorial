#pragma once

#include <string>

class Shader;

class ShaderProgram
{
public:
    explicit ShaderProgram(const std::string& filepath);
    ~ShaderProgram();

    bool IsValid() const;
    unsigned int GetId() const;
    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_id;
    Shader* m_vertexShader;
    Shader* m_fragmentShader;
};