#include "Cube.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "memory/MemoryTracker.h"

void* Cube::operator new(std::size_t size)
{
    if (size != sizeof(Cube))
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

void Cube::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Cube::Cube(int stackCount, int segmentCount)
{
    float stackStep = 1.0f / stackCount;
    float segmentStep = 1.0f / segmentCount;
    glm::vec3 normal(0.0f, 0.0f, 1.0f);
    int firstElementIndex = 0;

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f + j * segmentStep;
            float y = 0.5f - i * stackStep;
            float z = 0.5f;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f - i * stackStep;
            z = 0.5f;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(d, normal);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 3);
            firstElementIndex += 4;
        }
    }

    normal = glm::vec3(1.0f, 0.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = 0.5f;
            float y = 0.5f - i * stackStep;
            float z = 0.5f - j * segmentStep;
            glm::vec3 a(x, y, z);

            x = 0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f - j * segmentStep;
            glm::vec3 b(x, y, z);

            x = 0.5f;
            y = 0.5f - i * stackStep;
            z = 0.5f - (j + 1) * segmentStep;
            glm::vec3 c(x, y, z);

            x = 0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f - (j + 1) * segmentStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(d, normal);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 3);
            firstElementIndex += 4;
        }
    }

    normal = glm::vec3(0.0f, 0.0f, -1.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = 0.5f - j * segmentStep;
            float y = 0.5f - i * stackStep;
            float z = -0.5f;
            glm::vec3 a(x, y, z);

            x = 0.5f - j * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f;
            glm::vec3 b(x, y, z);

            x = 0.5f - (j + 1) * segmentStep;
            y = 0.5f - i * stackStep;
            z = -0.5f;
            glm::vec3 c(x, y, z);

            x = 0.5f - (j + 1) * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(d, normal);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 3);
            firstElementIndex += 4;
        }
    }

    normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f;
            float y = 0.5f - i * stackStep;
            float z = -0.5f + j * segmentStep;
            glm::vec3 a(x, y, z);

            x = -0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f + j * segmentStep;
            glm::vec3 b(x, y, z);

            x = -0.5f;
            y = 0.5f - i * stackStep;
            z = -0.5f + (j + 1) * segmentStep;
            glm::vec3 c(x, y, z);

            x = -0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f + (j + 1) * segmentStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(d, normal);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 3);
            firstElementIndex += 4;
        }
    }

    normal = glm::vec3(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f + j * segmentStep;
            float y = 0.5f;
            float z = -0.5f + i * stackStep;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * segmentStep;
            y = 0.5f;
            z = -0.5f + (i + 1) * stackStep;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f;
            z = -0.5f + i * stackStep;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f;
            z = -0.5f + (i + 1) * stackStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(d, normal);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 3);
            firstElementIndex += 4;
        }
    }

    normal = glm::vec3(0.0f, -1.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f + j * segmentStep;
            float y = -0.5f;
            float z = 0.5f - i * stackStep;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * segmentStep;
            y = -0.5f;
            z = 0.5f - (i + 1) * stackStep;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = -0.5f;
            z = 0.5f - i * stackStep;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = -0.5f;
            z = 0.5f - (i + 1) * stackStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(d, normal);
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