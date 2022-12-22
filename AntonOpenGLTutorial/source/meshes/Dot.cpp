#include "Dot.h"
#include <GL/glew.h>
#include "memory/MemoryTracker.h"

void* Dot::operator new(std::size_t size)
{
    if (size != sizeof(Dot))
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

void Dot::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Dot::Dot()
{
    m_enabled = false;
    AddAttribute(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    FinalizeGeometry();
}
void Dot::AddAttribute(const glm::vec3& point, const glm::vec3& normal)
{
    glDeleteBuffers(1, &m_attributesBuffer);
    glDeleteBuffers(1, &m_normalsBuffer);

    m_points.clear();
    m_normals.clear();
    m_points.push_back(point);
    m_normals.push_back(normal);
    FinalizeGeometry();
}

void Dot::Draw(std::shared_ptr<ShaderManager>& shaderManager) const
{
    if (!m_enabled)
    {
        return;
    }

    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glPointSize(1.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}