#include "BasicMesh.h"
#include "components/Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "materials/Material.h"
#include "memory/MemoryTracker.h"
#include "shaders/ShaderManager.h"

void* BasicMesh::operator new(std::size_t size)
{
    if (size != sizeof(BasicMesh))
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

void BasicMesh::operator delete(void* ptr, std::size_t size)
{
    MemoryTracker::RemoveMemoryUsage(size, MemoryCategory::Meshes);
    ::operator delete(ptr);
}

BasicMesh::BasicMesh()
    : m_sizeInBytes(0)
    , m_position(0.0f, 0.0f, 0.0f)
    , m_scale(1.0f, 1.0f, 1.0f)
    , m_enabled(true)
    , m_elementBuffer(0)
    , m_attributesBuffer(0)
{
    glGenVertexArrays(1, &m_attributeVertexArray);
    glBindVertexArray(m_attributeVertexArray);
}

BasicMesh::~BasicMesh()
{
    glBindVertexArray(m_attributeVertexArray);
    glDeleteBuffers(1, &m_elementBuffer);
    glDeleteBuffers(1, &m_attributesBuffer);
    glDeleteVertexArrays(1, &m_attributeVertexArray);
}

bool BasicMesh::IsEnabled() const
{
    return m_enabled;
}

void BasicMesh::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

void BasicMesh::AddAttribute(const glm::vec3& point)
{
    m_points.push_back(point);
}

void BasicMesh::AddElementIndex(unsigned int index)
{
    m_indices.push_back(index);
}

void BasicMesh::FinalizeGeometry()
{
    std::vector<float> attributes;

    for (size_t i = 0; i < m_points.size(); i++)
    {
        attributes.push_back(m_points[i].x);
        attributes.push_back(m_points[i].y);
        attributes.push_back(m_points[i].z);
    }

    glBindVertexArray(m_attributeVertexArray);
    glGenBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &m_attributesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_attributesBuffer);
    glBufferData(GL_ARRAY_BUFFER, attributes.size() * sizeof(float), attributes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void BasicMesh::AddComponent(std::unique_ptr<Component> component)
{
    component->OnAdded(this);
    m_components.push_back(std::move(component));
}

void BasicMesh::Update(float deltaSeconds)
{
    for (std::unique_ptr<Component>& component : m_components)
    {
        component->Update(deltaSeconds);
    }
}

void BasicMesh::PrepareShader(std::shared_ptr<Material> material, std::shared_ptr<ShaderManager>& shaderManager) const
{
    if (!material)
    {
        return;
    }

    const std::string& shaderName = material->GetShaderName();
    shaderManager->UseShader(shaderName);

    for (const std::pair<std::string, glm::vec3>& pair : material->GetVec3Uniforms())
    {
        glm::vec3 value = pair.second;
        shaderManager->SetUniform(shaderName, pair.first, 3, glm::value_ptr(value));
    }

    for (const std::pair<std::string, glm::vec4>& pair : material->GetVec4Uniforms())
    {
        glm::vec4 value = pair.second;
        shaderManager->SetUniform(shaderName, pair.first, 4, glm::value_ptr(value));
    }

    int textureSlot = 0;

    for (const std::pair<std::string, std::pair<std::shared_ptr<Texture>, unsigned int>>& pair : material->GetTextureUniforms())
    {
        const std::shared_ptr<Texture>& texture = pair.second.first;
        shaderManager->SetUniform(shaderName, pair.first, 1, &textureSlot);
        glActiveTexture(GL_TEXTURE0 + textureSlot);
        glBindTexture(GL_TEXTURE_2D, pair.second.second);
        textureSlot++;
    }

    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position) * m_rotation.ToMatrix() * glm::scale(glm::mat4(1.0f), m_scale);
    shaderManager->SetUniform(shaderName, "model", 4, 4, false, glm::value_ptr(model));
}

void BasicMesh::Draw(std::shared_ptr<ShaderManager>& shaderManager) const
{
    if (!m_material)
    {
        return;
    }

    glBindVertexArray(m_attributeVertexArray);
    PrepareShader(m_material, shaderManager);
    glEnable(GL_DEPTH_TEST);

    if (m_indices.size() > 0)
    {
        glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_points.size()));
    }
}