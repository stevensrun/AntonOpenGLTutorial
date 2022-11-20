#pragma once

#include <glm/glm.hpp>
#include "math/Quaternion.h"
#include <vector>

class Component;
class Material;
class ShaderManager;

class BasicMesh
{
public:
    BasicMesh();
    virtual ~BasicMesh();

    void* operator new(size_t size);
    void operator delete(void* ptr);

    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    virtual void AddAttribute(const glm::vec3& point);
    void AddComponent(Component* component);
    virtual void Update(float deltaSeconds);
    virtual void Draw(ShaderManager* shaderManager) const;

protected:
    virtual void FinalizeGeometry();
    virtual void PrepareShader(Material* material, ShaderManager* shaderManager) const;

public:
    Material* m_material;
    glm::vec3 m_position;
    Quaternion m_rotation;
    glm::vec3 m_scale;

protected:
    size_t m_sizeInBytes;
    std::vector<Component*> m_components;
    bool m_enabled;
    std::vector<glm::vec3> m_points;
    unsigned int m_attributeVertexArray;
    unsigned int m_attributesBuffer;
};