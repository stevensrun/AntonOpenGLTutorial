#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader(GLenum type, const std::string& source);
    ~Shader();

    bool IsValid() const;
    unsigned int GetId() const;

private:
    unsigned int m_id;
};