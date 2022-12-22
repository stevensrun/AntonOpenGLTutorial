#include "Triangle.h"
#include "memory/MemoryTracker.h"

void* Triangle::operator new(std::size_t size)
{
    if (size != sizeof(Triangle))
    {
        return ::operator new(size);
    }

    while (true)
    {
        void* ptr = ::operator new(size);

        if (ptr)
        {
            MemoryTracker::AddMemoryUsage(size, MemoryCategory::Meshes);
            return ptr;
        }

        std::new_handler handler = std::get_new_handler();

        if (!handler)
        {
            throw std::bad_alloc();
        }
    }
}

void Triangle::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Triangle::Triangle()
{
    AddAttribute(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    AddAttribute(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    AddAttribute(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    FinalizeGeometry();
}
