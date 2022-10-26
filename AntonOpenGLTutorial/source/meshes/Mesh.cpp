#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
    : m_enabled(true)
    , m_pointBuffer(0)
    , m_colorBuffer(0)
    , m_position(0.0f, 0.0f, 0.0f)
{
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);
}

Mesh::~Mesh()
{
    glBindVertexArray(m_vertexArray);
    glDeleteBuffers(1, &m_pointBuffer);
    glDeleteBuffers(1, &m_colorBuffer);
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
    glDeleteBuffers(1, &m_colorBuffer);
    m_points.clear();
    m_colors.clear();
    m_pointBuffer = 0;
    m_colorBuffer = 0;
}

void Mesh::AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute)
{
    m_points.push_back(point);
    m_colors.push_back(color);

    if (!lastAttribute)
    {
        return;
    }

    glGenBuffers(1, &m_pointBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_pointBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_points.size(), m_points.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_colors.size(), m_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);
}

void Mesh::Update(float deltaTimeInSeconds)
{
}