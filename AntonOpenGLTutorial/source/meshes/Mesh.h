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

    void SetEnabled(bool enabled);
    virtual void Update(float deltaTimeInSeconds);
    virtual void Draw(ShaderManager* shaderManager, Camera* camera, Light* light);
    virtual void DrawNormals(ShaderManager* shaderManager, Camera* camera);
    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal);
    virtual void AddComponent(Component* component);

protected:
    void FinalizeGeometry();
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal);
    virtual void PrepareShader(Material* material, ShaderManager* shaderManager, Camera* camera, Light* light);

public:
    glm::vec3 m_position;
    Quaternion m_rotation;
    glm::vec3 m_scale;
    Material* m_material;
    Material* m_normalMaterial;

protected:
    unsigned int m_attributeVertexArray;
    unsigned int m_normalVertexArray;
    unsigned int m_attributeBuffer;
    unsigned int m_normalBuffer;

    std::vector<glm::vec3> m_points;
    std::vector<glm::vec3> m_normals;

    bool m_enabled;
    std::vector<Component*> m_components;

};