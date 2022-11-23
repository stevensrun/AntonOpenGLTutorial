#include "Gizmo.h"
#include "camera/SceneCamera.h"
#include <GL/glew.h>
#include "memory/MemoryTracker.h"

void* Gizmo::operator new(size_t size)
{
    MemoryTracker::AddMemoryUsage(size, MemoryCategory::Meshes);
    Gizmo* gizmo = ::new Gizmo();
    return gizmo;
}

void Gizmo::operator delete(void* ptr)
{
    Gizmo* gizmo = reinterpret_cast<Gizmo*>(ptr);
    MemoryTracker::RemoveMemoryUsage(gizmo->m_sizeInBytes, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

void Gizmo::FinalizeGeometry()
{
    std::vector<float> attributes;

    for (size_t i = 0; i < m_points.size(); i++)
    {
        attributes.push_back(m_points[i].x);
        attributes.push_back(m_points[i].y);
        attributes.push_back(m_points[i].z);

        if (m_textureCoordinates.size() > 0)
        {
            attributes.push_back(m_textureCoordinates[i].s);
            attributes.push_back(m_textureCoordinates[i].t);
        }

        if (m_colors.size() > 0)
        {
            attributes.push_back(m_colors[i].r);
            attributes.push_back(m_colors[i].g);
            attributes.push_back(m_colors[i].b);
            attributes.push_back(m_colors[i].a);
        }
    }

    int stride = 3;

    if (m_textureCoordinates.size() > 0)
    {
        stride += 2 ;
    }

    if (m_colors.size() > 0)
    {
        stride += 4;
    }

    glBindVertexArray(m_attributeVertexArray);
    glGenBuffers(1, &m_attributesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_attributesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * attributes.size(), attributes.data(), GL_STATIC_DRAW);

    int offset = 0;
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    offset += 3;

    if (m_textureCoordinates.size() > 0)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, false, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(1);
        offset += 2;
    }

    if (m_colors.size() > 0)
    {
        glVertexAttribPointer(2, 4, GL_FLOAT, false, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}

void Gizmo::Update(float deltaTimeInSeconds, SceneCamera* camera)
{
}