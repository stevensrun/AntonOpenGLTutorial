#include "Texture.h"
#include <stb_image.h>

Texture::Texture(const std::string& filepath)
    : m_filepath(filepath)
    , m_data(nullptr)
    , m_width(0)
    , m_height(0)
    , m_channelCount(0)
{
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channelCount, 0);
}

Texture::~Texture()
{
    if (m_data)
    {
        delete m_data;
    }
}

const unsigned char* Texture::GetData() const
{
    return m_data;
}

int Texture::GetWidth() const
{
    return m_width;
}

int Texture::GetHeight() const
{
    return m_height;
}

int Texture::GetChannelCount() const
{
    return m_channelCount;
}

GLenum Texture::GetFormat() const
{
    return (GetChannelCount() == 3) ? GL_RGB : GL_RGBA;
}
