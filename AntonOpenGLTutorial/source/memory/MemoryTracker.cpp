#include "MemoryTracker.h"

std::unordered_map<MemoryCategory, size_t> MemoryTracker::s_memoryUsage;

void MemoryTracker::AddMemoryUsage(size_t sizeInBytes, MemoryCategory category)
{
    if (MemoryTracker::s_memoryUsage.find(category) == MemoryTracker::s_memoryUsage.end())
    {
        MemoryTracker::s_memoryUsage[category] = 0;
    }

    MemoryTracker::s_memoryUsage[category] += sizeInBytes;
}

void MemoryTracker::RemoveMemoryUsage(size_t sizeInBytes, MemoryCategory category)
{
    if (MemoryTracker::s_memoryUsage.find(category) == MemoryTracker::s_memoryUsage.end())
    {
        return;
    }

    MemoryTracker::s_memoryUsage[category] -= sizeInBytes;
}

const std::unordered_map<MemoryCategory, size_t>& MemoryTracker::GetAllMemoryUsage()
{
    return MemoryTracker::s_memoryUsage;
}

const size_t MemoryTracker::GetMemoryUsage(MemoryCategory category)
{
    size_t memoryUsageInBytes = 0;

    if (MemoryTracker::s_memoryUsage.find(category) != MemoryTracker::s_memoryUsage.end())
    {
        memoryUsageInBytes = MemoryTracker::s_memoryUsage[category];
    }

    return memoryUsageInBytes;
}
