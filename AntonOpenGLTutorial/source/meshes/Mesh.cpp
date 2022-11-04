#include "Mesh.h"
#include "components/Component.h"
#include <iostream>

Mesh::Mesh()
    : m_enabled(true)
    , m_pointBuffer(0)
    , m_normalBuffer(0)
    , m_colorBuffer(0)
    , m_ambientReflectivityBuffer(0)
    , m_diffuseReflectivityBuffer(0)
    , m_specularReflectivityBuffer(0)
    , m_position(0.0f, 0.0f, 0.0f)
{
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);
}

Mesh::~Mesh()
{
    glBindVertexArray(m_vertexArray);
    glDeleteBuffers(1, &m_pointBuffer);
    glDeleteBuffers(1, &m_normalBuffer);
    glDeleteBuffers(1, &m_colorBuffer);
    glDeleteBuffers(1, &m_ambientReflectivityBuffer);
    glDeleteBuffers(1, &m_diffuseReflectivityBuffer);
    glDeleteBuffers(1, &m_specularReflectivityBuffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void Mesh::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

void Mesh::ClearAttributes()
{
    glBindVertexArray(m_vertexArray);
    glDeleteBuffers(1, &m_pointBuffer);
    glDeleteBuffers(1, &m_normalBuffer);
    glDeleteBuffers(1, &m_colorBuffer);
    glDeleteBuffers(1, &m_ambientReflectivityBuffer);
    glDeleteBuffers(1, &m_diffuseReflectivityBuffer);
    glDeleteBuffers(1, &m_specularReflectivityBuffer);
    m_points.clear();
    m_normals.clear();
    m_colors.clear();
    m_ambientReflectivity.clear();
    m_diffuseReflectivity.clear();
    m_specularReflectivity.clear();
    m_pointBuffer = 0;
    m_normalBuffer = 0;
    m_colorBuffer = 0;
    m_ambientReflectivityBuffer = 0;
    m_diffuseReflectivityBuffer = 0;
    m_specularReflectivityBuffer = 0;
}

void Mesh::AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec4& color, const glm::vec3& ambientReflectivity, const glm::vec3& diffuseReflectivity, const glm::vec4& specularReflectivity, bool lastAttribute)
{
    m_points.push_back(point);
    m_normals.push_back(normal);
    m_colors.push_back(color);
    m_ambientReflectivity.push_back(ambientReflectivity);
    m_diffuseReflectivity.push_back(diffuseReflectivity);
    m_specularReflectivity.push_back(specularReflectivity);

    if (!lastAttribute)
    {
        return;
    }

    glGenBuffers(1, &m_pointBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_pointBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_points.size(), m_points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_normals.size(), m_normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_colors.size(), m_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &m_ambientReflectivityBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ambientReflectivityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_ambientReflectivity.size(), m_ambientReflectivity.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &m_diffuseReflectivityBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_diffuseReflectivityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_diffuseReflectivity.size(), m_diffuseReflectivity.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(4, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(4);

    glGenBuffers(1, &m_specularReflectivityBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_specularReflectivityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_specularReflectivity.size(), m_specularReflectivity.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(5, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(5);
}

void Mesh::Update(float deltaTimeInSeconds)
{
    for (Component* component : m_components)
    {
        component->Update(deltaTimeInSeconds);
    }
}

void Mesh::Draw()
{
    if (!m_enabled)
    {
        return;
    }

    glBindVertexArray(m_vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_points.size()));
}

bool Mesh::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    return false;
}

void Mesh::AddComponent(Component* component)
{
    component->OnAdded(this);
    m_components.push_back(component);
}