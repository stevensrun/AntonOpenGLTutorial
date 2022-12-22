#include "Plane.h"
#include "memory/MemoryTracker.h"

void* Plane::operator new(std::size_t size)
{
    if (size != sizeof(Plane))
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

void Plane::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Plane::Plane(int rows, int columns)
{
    float rowStep = 1.0f / rows;
    float columnStep = 1.0f / columns;
    glm::vec3 normal(0.0f, 1.0f, 0.0f);
    int firstElementIndex = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            float x = -0.5f + j * columnStep;
            float y = 0.0f;
            float z = -0.5f + i * rowStep;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * columnStep;
            y = 0.0f;
            z = -0.5f + (i + 1) * rowStep;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * columnStep;
            y = 0.0f;
            z = -0.5f + i * rowStep;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * columnStep;
            y = 0.0f;
            z = -0.5f + (i + 1) * rowStep;
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