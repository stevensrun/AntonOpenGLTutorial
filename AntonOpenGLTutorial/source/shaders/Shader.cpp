#include "Shader.h"

#include <iostream>

Shader::Shader(GLenum type, const std::string& source) noexcept
    : m_id(0)
{
    const char* sourceString = source.c_str();
    m_id = glCreateShader(type);
    glShaderSource(m_id, 1, &sourceString, nullptr);
    glCompileShader(m_id);

    int result;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);

    if (result)
    {
        return;
    }

    int length;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);
    char* log = new char[length];
    glGetShaderInfoLog(m_id, length, &length, log);

    if (type == GL_VERTEX_SHADER)
    {
        std::cerr << "Vertex Shader Error: " << log << "\n";
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        std::cerr << "Fragment Shader Error: " << log << "\n";
    }

    delete[] log;

    m_id = 0;
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

bool Shader::IsValid() const
{
    return m_id != 0;
}

unsigned int Shader::GetId() const
{
    return m_id;
}
