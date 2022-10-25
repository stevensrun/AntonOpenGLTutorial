#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
    : m_enabled(true)
    , m_positionBuffer(0)
    , m_colorBuffer(0)
{
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_positionBuffer);
    glDeleteBuffers(1, &m_colorBuffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void Mesh::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

void Mesh::AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute)
{
    m_positions.push_back(point);
    m_colors.push_back(color);

    if (!lastAttribute)
    {
        return;
    }

    glm::vec3 a(m_positions[0].x, m_positions[0].y, m_positions[0].z);
    glm::vec3 b(m_positions[1].x, m_positions[1].y, m_positions[1].z);

    glGenBuffers(1, &m_positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_positions.size(), m_positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_colors.size(), m_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);
}