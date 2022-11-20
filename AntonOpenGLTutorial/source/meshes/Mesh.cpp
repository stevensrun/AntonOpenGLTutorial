#include "Mesh.h"
#include "collisionShapes/TriangleShape.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "memory/MemoryTracker.h"

Mesh::Mesh()
    : m_normalMaterial(nullptr)
    , m_normalsBuffer(0)
{
    glGenVertexArrays(1, &m_normalVertexArray);
    glBindVertexArray(m_normalVertexArray);
}

Mesh::~Mesh()
{
    glBindVertexArray(m_normalVertexArray);
    glDeleteBuffers(1, &m_normalsBuffer);
    glDeleteVertexArrays(1, &m_normalVertexArray);
}

void* Mesh::operator new(size_t size)
{
    MemoryTracker::AddMemoryUsage(size, MemoryCategory::Meshes);
    Mesh* mesh = ::new Mesh();
    return mesh;
}

void Mesh::operator delete(void* ptr)
{
    Mesh* mesh = reinterpret_cast<Mesh*>(ptr);
    MemoryTracker::RemoveMemoryUsage(mesh->m_sizeInBytes, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

void Mesh::AddAttribute(const glm::vec3& point)
{
    BasicMesh::AddAttribute(point);
}

void Mesh::AddAttribute(const glm::vec3& point, const glm::vec3& normal)
{
    AddAttribute(point);
    m_normals.push_back(normal);
}

void Mesh::AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec2& textureCoordinate)
{
    AddAttribute(point, normal);
    m_textureCoordinates.push_back(textureCoordinate);
}

bool Mesh::HitTest(TriangleShape*& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface) const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position) * m_rotation.ToMatrix() * glm::scale(glm::mat4(1.0f), m_scale);

    for (int i = 0; i < m_points.size(); i += 3)
    {
        glm::vec4 a = model * glm::vec4(m_points[i], 1.0f);
        glm::vec4 b = model * glm::vec4(m_points[i + 1], 1.0f);
        glm::vec4 c = model * glm::vec4(m_points[i + 2], 1.0f);
        shape = new TriangleShape(a, b, c);
        bool hit = shape->HitTest(rayOrigin, rayDirection, hitPoint, hitNormal, allowBackface);

        if (hit)
        {
            return true;
        }

        delete shape;
        shape = nullptr;
    }

    return false;
}

void Mesh::FinalizeGeometry()
{
    std::vector<float> attributes;
    std::vector<float> normals;

    for (size_t i = 0; i < m_points.size(); i++)
    {
        attributes.push_back(m_points[i].x);
        attributes.push_back(m_points[i].y);
        attributes.push_back(m_points[i].z);
        attributes.push_back(m_normals[i].x);
        attributes.push_back(m_normals[i].y);
        attributes.push_back(m_normals[i].z);

        if (m_textureCoordinates.size() > 0)
        {
            attributes.push_back(m_textureCoordinates[i].s);
            attributes.push_back(m_textureCoordinates[i].t);
        }

        normals.push_back(m_points[i].x);
        normals.push_back(m_points[i].y);
        normals.push_back(m_points[i].z);

        glm::vec3 endPoint = m_points[i] + m_normals[i] * 0.1f;
        normals.push_back(endPoint.x);
        normals.push_back(endPoint.y);
        normals.push_back(endPoint.z);
    }

    int stride = 6 * sizeof(float);

    if (m_textureCoordinates.size() > 0)
    {
        stride += 2 * sizeof(float);
    }

    glBindVertexArray(m_attributeVertexArray);
    glGenBuffers(1, &m_attributesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_attributesBuffer);
    glBufferData(GL_ARRAY_BUFFER, attributes.size() * sizeof(float), attributes.data(), GL_STATIC_DRAW);

    int offset = 0;
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)offset);
    glEnableVertexAttribArray(0);
    offset += 3 * sizeof(float);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)offset);
    glEnableVertexAttribArray(1);
    offset += 3 * sizeof(float);

    if (m_textureCoordinates.size() > 0)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, false, stride, (void*)offset);
        glEnableVertexAttribArray(2);
        offset += 2 * sizeof(float);
    }

    glBindVertexArray(m_normalVertexArray);
    glGenBuffers(1, &m_normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Mesh::Draw(ShaderManager* shaderManager) const
{
    if (!m_material)
    {
        return;
    }

    glBindVertexArray(m_attributeVertexArray);
    PrepareShader(m_material, shaderManager);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_points.size()));
}

void Mesh::DrawNormals(ShaderManager* shaderManager) const
{
    if (!m_normalMaterial)
    {
        return;
    }

    PrepareShader(m_normalMaterial, shaderManager);
    glBindVertexArray(m_normalVertexArray);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_normals.size() * 2));
}
