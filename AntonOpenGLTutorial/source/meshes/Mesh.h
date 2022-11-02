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
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec4& color, const glm::vec3& ambientReflectivity, const glm::vec3& diffuseReflectivity, const glm::vec4& specularReflectivity, bool lastAttribute = false);
    virtual void Update(float deltaTimeInSeconds);
    virtual void Draw() = 0;

public:
    glm::vec3 m_position;
    Quaternion m_rotation;

protected:
    unsigned int m_vertexArray;
    unsigned int m_pointBuffer;
    unsigned int m_normalBuffer;
    unsigned int m_colorBuffer;
    unsigned int m_ambientReflectivityBuffer;
    unsigned int m_diffuseReflectivityBuffer;
    unsigned int m_specularReflectivityBuffer;

    std::vector<glm::vec3> m_points;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_ambientReflectivity;
    std::vector<glm::vec3> m_diffuseReflectivity;
    std::vector<glm::vec4> m_specularReflectivity;

    bool m_enabled;
};