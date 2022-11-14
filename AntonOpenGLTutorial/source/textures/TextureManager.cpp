#include "TextureManager.h"
#include "Texture.h"

Texture* TextureManager::GetTexture(const std::string& filepath)
{
    if (m_textures.find(filepath) != m_textures.end()) 
    {
        return m_textures[filepath];
    }

    Texture* texture = new Texture(filepath);

    if (texture->GetData() == nullptr)
    {
        return nullptr;
    }

    m_textures[filepath] = texture;
    return texture;
}
