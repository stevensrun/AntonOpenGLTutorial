#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();

    virtual float GetIntersectionParameter(const glm::vec3 rayOrigin, const glm::vec3& rayDirection) = 0;
    void SetEnabled(bool enabled);
    virtual void AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute = false);
    virtual void Draw() = 0;

protected:
    unsigned int m_vertexArray;
    unsigned int m_positionBuffer;
    unsigned int m_colorBuffer;

    bool m_enabled;
    std::vector<glm::vec4> m_positions;
    std::vector<glm::vec4> m_colors;
};