#include "AxisGizmo.h"
#include "camera/SceneCamera.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "memory/MemoryTracker.h"
#include <vector>

void* AxisGizmo::operator new(std::size_t size)
{
    if (size != sizeof(AxisGizmo))
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

void AxisGizmo::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

AxisGizmo::AxisGizmo()
{
    AddAttribute(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    AddAttribute(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    FinalizeGeometry();
}

void AxisGizmo::AddAttribute(const glm::vec3& point)
{
    BasicMesh::AddAttribute(point);
}

void AxisGizmo::AddAttribute(const glm::vec3& point, const glm::vec4& color)
{
    AddAttribute(point);
    m_colors.push_back(color);
}

void AxisGizmo::Update(float deltaTimeInSeconds, std::shared_ptr<SceneCamera>& camera) noexcept
{
    m_rotation = camera->GetRotation().GetInverse();
}

void AxisGizmo::Draw(std::shared_ptr<ShaderManager>& shaderManager) const
{
    PrepareShader(m_material, shaderManager);
    glBindVertexArray(m_attributeVertexArray);
    glLineWidth(1.5f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_points.size()));
}
