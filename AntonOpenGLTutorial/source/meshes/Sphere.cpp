#include "Sphere.h"
#include <glm/gtc/constants.hpp>
#include "memory/MemoryTracker.h"

void* Sphere::operator new(std::size_t size)
{
    if (size != sizeof(Sphere))
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

void Sphere::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Sphere::Sphere(float radius, int stackCount, int segmentCount)
{
    float stackStep = glm::pi<float>() / stackCount;
    float segmentStep = 2.0f * glm::pi<float>() / segmentCount;
    int firstElementIndex = 0;

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float stackAngle = glm::half_pi<float>() - i * stackStep;
            float chordLength = radius * cos(stackAngle);
            float segmentAngle = j * segmentStep;
            float x = chordLength * sin(segmentAngle);
            float y = radius * sin(stackAngle);
            float z = chordLength * cos(segmentAngle);
            glm::vec3 a(x, y, z);

            stackAngle = glm::half_pi<float>() - (i + 1) * stackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = j * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            stackAngle = glm::half_pi<float>() - i * stackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            stackAngle = glm::half_pi<float>() - (i + 1) * stackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 d(x, y, z);

            AddAttribute(a, a);
            AddAttribute(b, b);
            AddAttribute(c, c);
            AddAttribute(d, d);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 3);
            firstElementIndex += 4;
        }
    }

    FinalizeGeometry();
}