#pragma once

#include "BasicMesh.h"

class Material;
class TriangleShape;

class Mesh : public BasicMesh
{
public:
    Mesh();
    virtual ~Mesh();

    void* operator new(size_t size);
    void operator delete(void* ptr);

    virtual void AddAttribute(const glm::vec3& point) override;
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal);
    virtual void AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec2& textureCoordinate);
    virtual bool HitTest(TriangleShape*& shape, const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal, bool allowBackface = false) const;
    virtual void Draw(ShaderManager* shaderManager) const;
    virtual void DrawNormals(ShaderManager* shaderManager) const;

protected:
    virtual void FinalizeGeometry() override;

public:
    Material* m_normalMaterial;

protected:
    unsigned int m_normalVertexArray;
    unsigned int m_normalsBuffer;

    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_textureCoordinates;
};