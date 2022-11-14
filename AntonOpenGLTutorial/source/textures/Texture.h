#pragma once

#include <GL/glew.h>
#include <string>

class Texture
{
public:
    explicit Texture(const std::string& filepath);
    ~Texture();

    const unsigned char* GetData() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetChannelCount() const;
    GLenum GetFormat() const;

private:
    std::string m_filepath;
    unsigned char* m_data;
    int m_width;
    int m_height;
    int m_channelCount;
};