#pragma once

#include "meshes/BasicMesh.h"

class SceneCamera;

class Gizmo : public BasicMesh
{
public:
    Gizmo() = default;
    virtual ~Gizmo() = default;

    void* operator new(size_t size);
    void operator delete(void* ptr);

    virtual void Update(float deltaTimeInSeconds, SceneCamera* camera);

protected:
    virtual void FinalizeGeometry() override;

protected:
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec2> m_textureCoordinates;
};