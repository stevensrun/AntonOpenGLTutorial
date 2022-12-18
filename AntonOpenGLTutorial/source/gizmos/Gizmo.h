#pragma once

#include "meshes/BasicMesh.h"

class SceneCamera;

class Gizmo : public BasicMesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Gizmo() = default;
    virtual ~Gizmo() = default;

    virtual void Update(float deltaTimeInSeconds, SceneCamera* camera);

protected:
    virtual void FinalizeGeometry() override;

protected:
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec2> m_textureCoordinates;
};