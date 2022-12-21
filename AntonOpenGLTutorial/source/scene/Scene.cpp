#include "Scene.h"
#include "camera/SceneCamera.h"
#include "camera/UiCamera.h"
#include "collisionShapes/TriangleShape.h"
#include "components/Rotator.h"
#include "components/SlerpComponent.h"
#include <gizmos/AxisGizmo.h>
#include <glm/glm.hpp>
#include "lights/Light.h"
#include "materials/Material.h"
#include "meshes/Capsule.h"
#include "meshes/Cone.h"
#include "meshes/Cube.h"
#include "meshes/Cylinder.h"
#include "meshes/Dot.h"
#include "meshes/Line.h"
#include "meshes/Mesh.h"
#include "meshes/Plane.h"
#include "meshes/SierpinskiGasket.h"
#include "meshes/Sphere.h"
#include "meshes/Tetrahedron.h"
#include "meshes/Torus.h"
#include "meshes/Triangle.h"
#include "shaders/ShaderManager.h"

Scene::Scene()
{
    m_shaderManager = std::make_shared<ShaderManager>();
    m_shaderManager->LoadShader("gouraudShading", "shaders/gouraudShading.glsl");
    m_shaderManager->LoadShader("phongShading", "shaders/phongShading.glsl");
    m_shaderManager->LoadShader("blinnPhongShading", "shaders/blinnPhongShading.glsl");
    m_shaderManager->LoadShader("textureMap", "shaders/textureMap.glsl");
    m_shaderManager->LoadShader("ambientReflectivity", "shaders/ambientReflectivity.glsl");
    m_shaderManager->LoadShader("vertexColor", "shaders/vertexColor.glsl");
}

void Scene::Setup(int framebufferWidth, int framebufferHeight) noexcept
{
    m_sceneCamera = std::make_shared<SceneCamera>(glm::vec3(0.0f, 1.5f, 4.5f), 67.0f, static_cast<float>(framebufferWidth) / framebufferHeight);
    m_uiCamera = std::make_shared<UiCamera>(framebufferWidth, framebufferHeight);
    SetupGizmos();
    SetupLights();
    SetupMeshes();
}

void Scene::SetupGizmos() noexcept
{
    std::shared_ptr<Material> vertexColor = std::shared_ptr<Material>(new Material("vertexColor"));
    std::shared_ptr<AxisGizmo> axisGizmo = std::shared_ptr<AxisGizmo>(new AxisGizmo());
    axisGizmo->m_material = vertexColor;
    axisGizmo->m_position = glm::vec3(-0.9f, -0.75f, 0.0f);
    axisGizmo->m_scale = glm::vec3(0.05f, 0.05f, 0.05f);
    m_gizmos.push_back(axisGizmo);
}

void Scene::SetupLights() noexcept
{
    std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light(glm::vec3(0.0f, 3.0f, 4.0f)));
    light->m_ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    light->m_diffuseColor = glm::vec3(0.7f, 0.7f, 0.7f);
    light->m_specularColor = glm::vec3(0.4f, 0.2f, 0.7f);
    m_lights.push_back(light);
}

void Scene::SetupMeshes() noexcept
{
    std::shared_ptr<Material> blueCardboard = std::shared_ptr<Material>(new Material("phongShading"));
    blueCardboard->AddUniform("ambientReflectivity", glm::vec3(0.2f, 0.2f, 0.2f));
    blueCardboard->AddUniform("diffuseReflectivity", glm::vec3(0.0f, 0.0f, 1.0f));
    blueCardboard->AddUniform("specularReflectivity", glm::vec4(1.0f, 1.0f, 1.0f, 250.0f));

    std::shared_ptr<Triangle> triangle = std::shared_ptr<Triangle>(new Triangle());
    triangle->m_material = blueCardboard;
    m_meshes.push_back(triangle);

    std::shared_ptr<Cube> cube = std::shared_ptr<Cube>(new Cube(2, 2));
    cube->m_material = blueCardboard;
    cube->m_position = glm::vec3(-3.0f, 0.0f, 0.0f);
    m_meshes.push_back(cube);

    std::shared_ptr<Torus> torus = std::shared_ptr<Torus>(new Torus(0.3f, 0.2f, 16, 32));
    torus->m_material = blueCardboard;
    torus->m_position = glm::vec3(-1.25f, 0.0f, 0.0f);
    m_meshes.push_back(torus);

    std::shared_ptr<Sphere> sphere = std::shared_ptr<Sphere>(new Sphere(0.5f, 16, 24));
    sphere->m_material = blueCardboard;
    sphere->m_position = glm::vec3(1.0f, 0.0f, 0.0f);
    m_meshes.push_back(sphere);

    std::shared_ptr<Tetrahedron> tetraSphere = std::shared_ptr<Tetrahedron>(new Tetrahedron(4, true));
    tetraSphere->m_material = blueCardboard;
    tetraSphere->m_position = glm::vec3(3.0f, 0.0f, 0.0f);
    m_meshes.push_back(tetraSphere);

    std::shared_ptr<Material> lightGray = std::shared_ptr<Material>(new Material("blinnPhongShading"));
    lightGray->AddUniform("ambientReflectivity", glm::vec3(0.2f, 0.2f, 0.2f));
    lightGray->AddUniform("diffuseReflectivity", glm::vec3(0.8f, 0.8f, 0.8f));
    lightGray->AddUniform("specularReflectivity", glm::vec4(1.0f, 1.0f, 1.0f, 400.0f));

    std::shared_ptr<Plane> plane = std::shared_ptr<Plane>(new Plane(3, 3));
    plane->m_material = lightGray;
    plane->m_position = glm::vec3(0.0f, -2.0f, 0.0f);
    plane->m_scale = glm::vec3(15.0f, 1.0f, 10.0f);
    m_meshes.push_back(plane);
}

std::shared_ptr<ShaderManager>& Scene::GetShaderManager() noexcept
{
    return m_shaderManager;
}

std::shared_ptr<SceneCamera>& Scene::GetSceneCamera() noexcept
{
    return m_sceneCamera;
}

std::shared_ptr<UiCamera>& Scene::GetUiCamera() noexcept
{
    return m_uiCamera;
}

const std::vector<std::shared_ptr<Light>>& Scene::GetLights() const noexcept
{
    return m_lights;
}

std::vector<std::shared_ptr<BasicMesh>> Scene::GetMeshes() const noexcept
{
    std::vector<std::shared_ptr<BasicMesh>> meshes = m_meshes;

    if (m_dot && m_dot->IsEnabled())
    {
        meshes.push_back(m_dot);
    }

    return meshes;
}

const std::vector<std::shared_ptr<Gizmo>>& Scene::GetGizmos() const noexcept
{
    return m_gizmos;
}

void Scene::Update(float deltaSeconds) noexcept
{
    m_sceneCamera->Update(deltaSeconds);

    for (std::shared_ptr<BasicMesh>& mesh : m_meshes)
    {
        mesh->Update(deltaSeconds);
    }

    for (std::shared_ptr<Gizmo>& gizmos : m_gizmos)
    {
        gizmos->Update(deltaSeconds, m_sceneCamera);
    }
}

void Scene::OnMouseClick(float mouseX, float mouseY, int width, int height) noexcept
{
    float x = (2.0f * mouseX) / width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / height;
    //No need to convert viewport coordinates -> NDC because NDC -> clip is technically a multiplication by w however we have no depth to the ray so we can go from viewport coordinates -> clipCoordinates directly.
    glm::vec4 ray_clipCoordinates = glm::vec4(x, y, -1.0f, 1.0f);
    glm::vec4 ray_eyeCoordinates = glm::inverse(m_sceneCamera->GetProjection()) * ray_clipCoordinates;
    glm::vec4 ray_worldCoordinates = glm::inverse(m_sceneCamera->GetView()) * glm::vec4(ray_eyeCoordinates.x, ray_eyeCoordinates.y, -1.0f, 0.0f);
    glm::vec3 rayDirection = glm::normalize(glm::vec3(ray_worldCoordinates.x, ray_worldCoordinates.y, ray_worldCoordinates.z));

    for (int i = static_cast<int>(m_meshes.size()) - 1; i >= 0; i--)
    {
        std::shared_ptr<TriangleShape> shape = std::dynamic_pointer_cast<TriangleShape>(m_meshes[i]);

        if (!shape)
        {
            continue;
        }

        m_meshes.erase(m_meshes.begin() + i);
    }

    if (m_dot)
    {
        m_dot->SetEnabled(false);
    }

    std::shared_ptr<TriangleShape> shape;

    for (int i = static_cast<int>(m_meshes.size()) - 1; i >= 0; i--)
    {
        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(m_meshes[i]);

        if (!mesh)
        {
            continue;
        }

        glm::vec3 hitPosition;
        glm::vec3 hitNormal;
        bool hit = mesh->HitTest(shape, m_sceneCamera->GetPosition(), rayDirection, hitPosition, hitNormal);

        if (!hit)
        {
            continue;
        }

        if (m_dot)
        {
            m_dot->AddAttribute(hitPosition, hitNormal);
            m_dot->SetEnabled(true);
        }

        if (shape)
        {
            std::shared_ptr<Material> colorMaterial = std::make_shared<Material>("ambientReflectivity");
            colorMaterial->AddUniform("ambientReflectivity", glm::vec3(0.0f, 1.0f, 1.0f));
            shape->m_material = colorMaterial;
            m_meshes.push_back(shape);
        }

        break;
    }
}