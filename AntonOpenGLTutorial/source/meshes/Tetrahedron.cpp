#include "Tetrahedron.h"
#include "memory/MemoryTracker.h"

void* Tetrahedron::operator new(std::size_t size)
{
    if (size != sizeof(Tetrahedron))
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

void Tetrahedron::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Tetrahedron::Tetrahedron(int subdivisionCount, bool useVertexNormals)
    : m_useVertexNormals(useVertexNormals)
    , m_firstElementIndex(0)
{
    glm::vec3 a(0.0f, 0.9f, -0.333f);
    glm::vec3 b(0.0f, 0.0f, 1.0f);
    glm::vec3 c(0.816f, -0.471f, -0.333f);
    glm::vec3 d(-0.816f, -0.471f, -0.333f);

    divideTriangle(a, b, c, subdivisionCount);
    divideTriangle(a, d, b, subdivisionCount);
    divideTriangle(b, d, c, subdivisionCount);
    divideTriangle(a, c, d, subdivisionCount);
    FinalizeGeometry();
}

void Tetrahedron::divideTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int recursiveCount)
{
    if (recursiveCount == 0)
    {
        if (m_useVertexNormals)
        {
            AddAttribute(a, a);
            AddAttribute(b, b);
            AddAttribute(c, c);
        }
        else
        {
            glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
        }

        AddElementIndex(m_firstElementIndex);
        AddElementIndex(m_firstElementIndex + 1);
        AddElementIndex(m_firstElementIndex + 2);
        m_firstElementIndex += 3;
    }
    else
    {
        glm::vec3 u = glm::normalize((a + b) / 2.0f);
        glm::vec3 v = glm::normalize((b + c) / 2.0f);
        glm::vec3 w = glm::normalize((c + a) / 2.0f);
        divideTriangle(a, u, w, recursiveCount - 1);
        divideTriangle(b, v, u, recursiveCount - 1);
        divideTriangle(c, w, v, recursiveCount - 1);
        divideTriangle(u, v, w, recursiveCount - 1);
    }
}