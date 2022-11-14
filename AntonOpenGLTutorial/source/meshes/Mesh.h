#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "math/Quaternion.h"
#include <vector>

class Camera;
class Component;
class Light;
class Material;
class ShaderManager;

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();

    bool IsEnabled() const;
    void SetEnabled(bool enabled);
    virtual void Update(float deltaSeconds);
    virtual void Draw(ShaderManager* shaderManager) const;
    virtual void DrawNormals(ShaderManager* shaderManager) const;
    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal) const;
    virtual void AddComponent(Component* component);

protected:
    void FinalizeGeometry();
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal);
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec2& textureCoordinate);
    virtual void PrepareShader(Material* material, ShaderManager* shaderManager) const;

public:
    glm::vec3 m_position;
    Quaternion m_rotation;
    glm::vec3 m_scale;
    Material* m_material;
    Material* m_normalMaterial;

protected:
    unsigned int m_attributeVertexArray;
    unsigned int m_normalVertexArray;
    unsigned int m_attributesBuffer;
    unsigned int m_normalsBuffer;

    std::vector<glm::vec3> m_points;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_textureCoordinates;

    bool m_enabled;
    std::vector<Component*> m_components;

};