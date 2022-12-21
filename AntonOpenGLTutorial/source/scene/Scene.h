#pragma once

#include <memory>
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
    Scene(const Scene& rhs) = delete;
    Scene(const Scene&& rhs) = delete;
    virtual ~Scene() = default;

    Scene& operator=(const Scene& rhs) = delete;

    std::shared_ptr<ShaderManager>& GetShaderManager() noexcept;
    std::shared_ptr<SceneCamera>& GetSceneCamera() noexcept;
    std::shared_ptr<UiCamera>& GetUiCamera() noexcept;
    const std::vector< std::shared_ptr<Light>>& GetLights() const noexcept;
    std::vector< std::shared_ptr<BasicMesh>> GetMeshes() const noexcept;
    const std::vector<std::shared_ptr<Gizmo>>& GetGizmos() const noexcept;
    void Setup(int framebufferWidth, int framebufferHeight) noexcept;
    void Update(float deltaSeconds) noexcept;
    void OnMouseClick(float mouseX, float mouseY, int width, int height) noexcept;

protected:
    void SetupGizmos() noexcept;
    void SetupLights() noexcept;
    void SetupMeshes() noexcept;

protected:
    std::shared_ptr<ShaderManager> m_shaderManager;
    std::shared_ptr<SceneCamera> m_sceneCamera;
    std::shared_ptr<UiCamera> m_uiCamera;
    std::vector< std::shared_ptr<Light>> m_lights;
    std::vector< std::shared_ptr<BasicMesh>> m_meshes;
    std::vector<std::shared_ptr<Gizmo>> m_gizmos;
    std::shared_ptr<Dot> m_dot;
};