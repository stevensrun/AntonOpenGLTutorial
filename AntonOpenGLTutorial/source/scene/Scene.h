#pragma once

#include <vector>

class BasicMesh;
class Dot;
class Gizmo;
class Light;
class SceneCamera;
class ShaderManager;
class TriangleShape;
class UiCamera;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    ShaderManager* GetShaderManager() const;
    SceneCamera* GetSceneCamera();
    UiCamera* GetUiCamera();
    const std::vector<Light*>& GetLights() const;
    std::vector<BasicMesh*> GetMeshes() const;
    const std::vector<Gizmo*>& GetGizmos() const;
    void Setup(int framebufferWidth, int framebufferHeight);
    void Update(float deltaSeconds);
    void OnMouseClick(float mouseX, float mouseY, int width, int height);

protected:
    void SetupGizmos();
    void SetupLights();
    void SetupMeshes();

protected:
    ShaderManager* m_shaderManager;
    SceneCamera* m_sceneCamera;
    UiCamera* m_uiCamera;
    std::vector<Light*> m_lights;
    std::vector<BasicMesh*> m_meshes;
    std::vector<Gizmo*> m_gizmos;
    Dot* m_dot;
};