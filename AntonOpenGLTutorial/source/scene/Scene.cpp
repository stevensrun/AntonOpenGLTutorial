#include "Scene.h"
#include "camera/Camera.h"
#include "components/Rotator.h"
#include "lights/Light.h"
#include "materials/Material.h"
#include "meshes/Cone.h"
#include "meshes/Cube.h"
#include "meshes/Cylinder.h"
#include "meshes/Dot.h"
#include "meshes/Line.h"
#include "meshes/Mesh.h"
#include "meshes/Plane.h"
#include "meshes/Sphere.h"
#include "meshes/Triangle.h"

Scene::Scene()
    : m_camera(nullptr)
{
}

Scene::~Scene()
{
    if (m_camera)
    {
        delete m_camera;
    }
}

void Scene::Setup()
{
    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    SetupLights();
    SetupMeshes();
}

void Scene::SetupLights()
{
    Light* light = new Light(glm::vec3(0.0f, 0.0f, 3.0f));
    light->m_ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    light->m_diffuseColor = glm::vec3(0.7f, 0.7f, 0.7f);
    light->m_specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
    m_lights.push_back(light);
}

void Scene::SetupMeshes()
{
    Material* normalMaterial = new Material("ambientReflectivity");
    normalMaterial->AddUniform("ambientReflectivity", glm::vec3(1.0f, 0.0f, 0.0f));

    Material* textureMaterial = new Material("textureMap");
    textureMaterial->AddTextureUniform("baseTexture", "textures/skulluvmap.png");
    textureMaterial->AddTextureUniform("secondaryTexture", "textures/sandstone.png");

    Plane* skullPlane = new Plane();
    skullPlane->m_material = textureMaterial;
    skullPlane->m_normalMaterial = normalMaterial;
    skullPlane->m_position = glm::vec3(-2.0f, 0.0f, 0.0f);
    skullPlane->m_scale = glm::vec3(0.5f, 1.0f, 0.5f);
    skullPlane->m_rotation = Quaternion::AngleAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    m_meshes.push_back(skullPlane);

    Material* material = new Material("blinnPhongShading");
    material->AddUniform("ambientReflectivity", glm::vec3(1.0f, 1.0f, 1.0f));
    material->AddUniform("diffuseReflectivity", glm::vec3(1.0f, 0.5f, 0.0f));
    material->AddUniform("specularReflectivity", glm::vec4(1.0f, 1.0f, 1.0f, 150.0f));

    Sphere* sphere = new Sphere(1.0f, 16, 32);
    sphere->m_material = material;
    sphere->m_normalMaterial = normalMaterial;
    sphere->m_rotation = Quaternion::AngleAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    sphere->AddComponent(new Rotator(15.0f, glm::vec3(1.0f, 1.0f, 0.0f)));
    m_meshes.push_back(sphere);

    Cone* cone = new Cone(1.0f, 0.5f, 16, 32);
    cone->m_material = material;
    cone->m_normalMaterial = normalMaterial;
    cone->m_position = glm::vec3(2.0f, 0.0f, 0.0f);
    m_meshes.push_back(cone);
}

Camera* Scene::GetCamera()
{
    return m_camera;
}

const std::vector<Light*>& Scene::GetLights() const
{
    return m_lights;
}

const std::vector<Mesh*>& Scene::GetMeshes() const
{
    return m_meshes;
}

void Scene::Update(float deltaSeconds)
{
    m_camera->Update(deltaSeconds);

    for (Mesh* mesh : m_meshes)
    {
        mesh->Update(deltaSeconds);
    }
}

void Scene::OnMouseClick(float mouseX, float mouseY, int width, int height)
{

}