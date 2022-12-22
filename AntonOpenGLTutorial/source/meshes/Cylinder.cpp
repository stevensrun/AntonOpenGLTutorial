#include "Cylinder.h"
#include <glm/ext.hpp>
#include <glm/gtc/constants.hpp>
#include "memory/MemoryTracker.h"

void* Cylinder::operator new(std::size_t size)
{
    if (size != sizeof(Cylinder))
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

void Cylinder::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Cylinder::Cylinder(float height, float radius, int stackCount, int segmentCount)
{
    float heightStep = height / stackCount;
    float segmentStep = 2.0f * glm::pi<float>() / segmentCount;

    for (int i = 0; i < stackCount; i++)
    {
        float top = height / 2.0f - i * heightStep;

        for (int j = 0; j < segmentCount; j++)
        {
            float segmentAngle = j * segmentStep;
            float x = radius * sin(segmentAngle);
            float y = top;
            float z = radius * cos(segmentAngle);
            glm::vec3 a(x, y, z);

            x = radius * sin(segmentAngle);
            y = top - heightStep;
            z = radius * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            segmentAngle = (j + 1) * segmentStep;
            x = radius * sin(segmentAngle);
            y = top;
            z = radius * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            segmentAngle = (j + 1) * segmentStep;
            x = radius * sin(segmentAngle);
            y = top - heightStep;
            z = radius * cos(segmentAngle);
            glm::vec3 d(x, y, z);


            AddAttribute(a, glm::vec3(a.x, 0.0f, a.z));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z));
            AddAttribute(d, glm::vec3(d.x, 0.0f, d.z));
        }
    }

    for (int i = 0; i < 2; i++)
    {
        float y = height / 2.0f - i * height;
        float x = 0.0f;
        float z = 0.0f;
        glm::vec3 a(x, y, z);

        for (int j = 0; j < segmentCount; j++)
        {
            float segmentAngle = j * segmentStep;
            x = radius * sin(segmentAngle);
            z = radius * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            segmentAngle = (j + 1) * segmentStep;
            x = radius * sin(segmentAngle);
            z = radius * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            if (i == 0)
            {
                AddAttribute(a, glm::vec3(0.0f, std::copysign(1.0f, y), 0.0f));
                AddAttribute(b, glm::vec3(0.0f, std::copysign(1.0f, y), 0.0f));
                AddAttribute(c, glm::vec3(0.0f, std::copysign(1.0f, y), 0.0f));
            }
            else
            {
                AddAttribute(c, glm::vec3(0.0f, std::copysign(1.0f, y), 0.0f));
                AddAttribute(b, glm::vec3(0.0f, std::copysign(1.0f, y), 0.0f));
                AddAttribute(a, glm::vec3(0.0f, std::copysign(1.0f, y), 0.0f));
            }
        }
    }

    FinalizeGeometry();
}
