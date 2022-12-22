#include "Cone.h"
#include <glm/ext.hpp>
#include "memory/MemoryTracker.h"

void* Cone::operator new(std::size_t size)
{
    if (size != sizeof(Cone))
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

void Cone::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Cone::Cone(float height, float radius, int stackCount, int segmentCount)
{
    float segmentStep = 2 * glm::pi<float>() / segmentCount;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), segmentStep, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 a(0.0f, height / 2.0f, 0.0f);
    glm::vec3 b(0.0f, -height / 2.0f, radius);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            glm::vec3 c = glm::vec3(rotation * glm::vec4(b, 1.0f));
            AddAttribute(a, glm::vec3(a.x, 0.0f, a.z));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z));
            b = c;
        }
    }

    glm::vec3 d(0.0f, -height / 2.0f, 0.0f);
    float x = 0.0;
    float y = -height / 2.0f;
    float z = radius;
    glm::vec3 f(x, y, z);

    for (int i = 0; i < segmentCount; i++)
    {
        float segmentAngle = (i + 1) * segmentStep;
        float x = radius * sin(segmentAngle);
        float z = radius * cos(segmentAngle);
        glm::vec3 e(x, y, z);

        AddAttribute(d, glm::vec3(0.0f, -1.0f, 0.0f));
        AddAttribute(e, glm::vec3(0.0f, -1.0f, 0.0f));
        AddAttribute(f, glm::vec3(0.0f, -1.0f, 0.0f));
        f = e;
    }

    FinalizeGeometry();
}
