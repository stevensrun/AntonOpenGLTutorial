#include "TextureManager.h"
#include "Texture.h"

std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& filepath) noexcept
{
    if (m_textures.find(filepath) != m_textures.end()) 
    {
        return m_textures[filepath];
    }

    std::shared_ptr<Texture> texture = std::make_shared<Texture>(filepath);

    if (texture->GetData() == nullptr)
    {
        return nullptr;
    }

    m_textures[filepath] = texture;
    return texture;
}
