#pragma once

#include <vector>

class Camera;
class Dot;
class Light;
class Mesh;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    Camera* GetCamera();
    const std::vector<Light*>& GetLights() const;
    std::vector<Mesh*> GetMeshes() const;
    void Setup();
    void Update(float deltaSeconds);
    void OnMouseClick(float mouseX, float mouseY, int width, int height);

protected:
    void SetupLights();
    void SetupMeshes();

protected:
    Camera* m_camera;
    std::vector<Light*> m_lights;
    std::vector<Mesh*> m_meshes;
    Dot* m_dot;
};