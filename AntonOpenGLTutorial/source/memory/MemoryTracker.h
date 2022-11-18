#pragma once

#include <unordered_map>

enum class MemoryCategory
{
    CollisionShapes,
    Lights,
    Meshes,
    Shaders,
    Textures,
};

class MemoryTracker
{
public:
    static void AddMemoryUsage(size_t sizeInBytes, MemoryCategory category);
    static void RemoveMemoryUsage(size_t sizeInBytes, MemoryCategory category);
    static const std::unordered_map<MemoryCategory, size_t>& GetAllMemoryUsage();
    static const size_t GetMemoryUsage(MemoryCategory category);

private:
    MemoryTracker() = default;

private:
    static std::unordered_map<MemoryCategory, size_t> s_memoryUsage;
};