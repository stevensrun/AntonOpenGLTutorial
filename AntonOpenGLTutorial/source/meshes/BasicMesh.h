#pragma once

#include <glm/glm.hpp>
#include "math/Quaternion.h"
#include <memory>
#include <vector>

class Component;
class Material;
class ShaderManager;

class BasicMesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    BasicMesh();
    virtual ~BasicMesh();

    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    virtual void AddAttribute(const glm::vec3& point);
    virtual void AddElementIndex(unsigned int index);
    void AddComponent(std::unique_ptr<Component> component);
    virtual void Update(float deltaSeconds);
    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const;

protected:
    virtual void FinalizeGeometry();
    virtual void PrepareShader(std::shared_ptr<Material> material, std::shared_ptr<ShaderManager>& shaderManager) const;

public:
    std::shared_ptr<Material> m_material;
    glm::vec3 m_position;
    Quaternion m_rotation;
    glm::vec3 m_scale;

protected:
    std::size_t m_sizeInBytes;
    std::vector<std::unique_ptr<Component>> m_components;
    bool m_enabled;
    std::vector<glm::vec3> m_points;
    std::vector<unsigned int> m_indices;
    unsigned int m_attributeVertexArray;
    unsigned int m_elementBuffer;
    unsigned int m_attributesBuffer;
};