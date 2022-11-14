#pragma once

#include <string>
#include <unordered_map>

class Texture;

class TextureManager
{
public:
    TextureManager() = default;
    ~TextureManager() = default;

    Texture* GetTexture(const std::string& filepath);

private:
    std::unordered_map<std::string, Texture*> m_textures;
};