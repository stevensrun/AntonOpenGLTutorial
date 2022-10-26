#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "math/Quaternion.h"
#include <vector>

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();

    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal) = 0;
    void SetEnabled(bool enabled);
    virtual void ClearAttributes();
    virtual void AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute = false);
    virtual void Update(float deltaTimeInSeconds);
    virtual void Draw() = 0;

public:
    glm::vec3 m_position;
    Quaternion m_rotation;

protected:
    unsigned int m_vertexArray;
    unsigned int m_pointBuffer;
    unsigned int m_colorBuffer;

    std::vector<glm::vec4> m_points;
    std::vector<glm::vec4> m_colors;

    bool m_enabled;
};