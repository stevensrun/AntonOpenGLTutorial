#pragma once

#include <GL/glew.h>
#include <string>

class Shader final
{
public:
    Shader(GLenum type, const std::string& source) noexcept;
    ~Shader();

    bool IsValid() const;
    unsigned int GetId() const;

private:
    unsigned int m_id;
};