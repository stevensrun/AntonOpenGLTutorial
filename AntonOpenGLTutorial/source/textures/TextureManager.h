#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Texture;

class TextureManager final
{
public:
    TextureManager() = default;
    ~TextureManager() = default;

    std::shared_ptr<Texture> GetTexture(const std::string& filepath) noexcept;

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
};