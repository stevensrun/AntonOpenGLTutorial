#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include "Shader.h"
#include <sstream>

ShaderProgram::ShaderProgram(const std::string& filepath) noexcept
    : m_id(0)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << filepath << "\n";
        return;
    }

    enum class ShaderType
    {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    ShaderType shaderType = ShaderType::None;
    std::stringstream ss[2];
    std::string line;

    while (std::getline(file, line))
    {
        if (line.find("#SHADER") != std::string::npos)
        {
            if (line.find("VERTEX") != std::string::npos)
            {
                shaderType = ShaderType::Vertex;
            }
            else if (line.find("FRAGMENT") != std::string::npos)
            {
                shaderType = ShaderType::Fragment;
            }
        }
        else
        {
            ss[static_cast<int>(shaderType)] << line << "\n";
        }
    }

    file.close();

    m_vertexShader.reset(new Shader(GL_VERTEX_SHADER, ss[0].str()));
    m_fragmentShader.reset(new Shader(GL_FRAGMENT_SHADER, ss[1].str()));

    if (!m_vertexShader->IsValid() || !m_fragmentShader->IsValid())
    {
        return;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, m_vertexShader->GetId());
    glAttachShader(m_id, m_fragmentShader->GetId());
    glLinkProgram(m_id);
    glDetachShader(m_id, m_vertexShader->GetId());
    glDetachShader(m_id, m_fragmentShader->GetId());

    int result;
    glGetProgramiv(m_id, GL_LINK_STATUS, &result);

    if (result)
    {
        return;
    }

    int length;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
    char* log = new char[length];
    glGetProgramInfoLog(m_id, length, &length, log);
    std::cerr << "Shader Program Error: " << " File: " << filepath << " : " << log << "\n";
    delete[] log;

    m_id = 0;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

bool ShaderProgram::IsValid() const noexcept
{
    return m_id != 0;
}

unsigned int ShaderProgram::GetId() const noexcept
{
    return m_id;
}

void ShaderProgram::Bind() const noexcept
{
    glUseProgram(m_id);
}

void ShaderProgram::Unbind() const noexcept
{
    glUseProgram(0);
}
