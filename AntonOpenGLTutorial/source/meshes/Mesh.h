#pragma once

#include "BasicMesh.h"

class Material;
class TriangleShape;

class Mesh : public BasicMesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Mesh();
    virtual ~Mesh();

    virtual void AddAttribute(const glm::vec3& point) override;
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal);
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec2& textureCoordinate);
    virtual bool HitTest(std::shared_ptr<TriangleShape>& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface = false) const;
    virtual void Draw(std::shared_ptr<ShaderManager>& shaderManager) const;
    virtual void DrawNormals(std::shared_ptr<ShaderManager>& shaderManager) const;

protected:
    virtual void FinalizeGeometry() override;

public:
    std::shared_ptr<Material> m_normalMaterial;

protected:
    unsigned int m_normalVertexArray;
    unsigned int m_normalsBuffer;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_textureCoordinates;
};