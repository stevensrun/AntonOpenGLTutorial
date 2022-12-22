#include "Line.h"
#include <GL/glew.h>
#include "memory/MemoryTracker.h"

void* Line::operator new(std::size_t size)
{
    if (size != sizeof(Line))
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

void Line::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

Line::Line(const glm::vec3& p0, const glm::vec3 p1)
{
    AddAttribute(p0);
    AddAttribute(p1);
    FinalizeGeometry();
}

void Line::Draw(std::shared_ptr<ShaderManager>& shaderManager) const
{
    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glDisable(GL_DEPTH_TEST);
    glLineWidth(6.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_points.size()));
}