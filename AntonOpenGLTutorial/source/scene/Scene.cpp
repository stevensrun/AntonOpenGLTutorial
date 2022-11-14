#include "Scene.h"
#include "camera/Camera.h"
#include "components/Rotator.h"
#include <glm/glm.hpp>
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
    , m_dot(nullptr)
{
}

Scene::~Scene()
{
    if (m_camera)
    {
        delete m_camera;
    }

    if (m_dot)
    {
        delete m_dot;
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
    light->m_specularColor = glm::vec3(0.4f, 0.2f, 0.7f);
    m_lights.push_back(light);
}

void Scene::SetupMeshes()
{
    Material* normalMaterial = new Material("ambientReflectivity");
    normalMaterial->AddUniform("ambientReflectivity", glm::vec3(1.0f, 0.0f, 0.0f));

    Material* material = new Material("phongShading");
    material->AddUniform("ambientReflectivity", glm::vec3(0.2f, 0.2f, 0.2f));
    material->AddUniform("diffuseReflectivity", glm::vec3(1.0f, 0.7f, 0.7f));
    material->AddUniform("specularReflectivity", glm::vec4(0.7f, 0.7f, 0.7f, 200.0f));

    Triangle* triangle = new Triangle();
    triangle->m_material = material;
    triangle->m_normalMaterial = normalMaterial;
    triangle->m_position = glm::vec3(0.0f, 0.0f, 2.0f);
    triangle->m_rotation = Quaternion::AngleAxis(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    m_meshes.push_back(triangle);

    Cube* cube = new Cube();
    cube->m_material = material;
    cube->m_normalMaterial = normalMaterial;
    cube->m_position = glm::vec3(2.0f, 0.0f, 0.0f);
    cube->m_rotation = Quaternion::AngleAxis(45.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    m_meshes.push_back(cube);

    Material* dotMaterial = new Material("ambientReflectivity");
    dotMaterial->AddUniform("ambientReflectivity", glm::vec3(0.0f, 1.0f, 0.0f));

    m_dot = new Dot();
    m_dot->m_material = dotMaterial;
    m_dot->SetEnabled(false);
}

Camera* Scene::GetCamera()
{
    return m_camera;
}

const std::vector<Light*>& Scene::GetLights() const
{
    return m_lights;
}

std::vector<Mesh*> Scene::GetMeshes() const
{
    std::vector<Mesh*> meshes = m_meshes;

    if (m_dot && m_dot->IsEnabled())
    {
        meshes.push_back(m_dot);
    }

    return meshes;
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
    float x = (2.0f * mouseX) / width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / height;
    //No need to convert viewport coordinates -> NDC because NDC -> clip is technically a multiplication by w however we have no depth to the ray so we can go from viewport coordinates -> clipCoordinates directly.
    glm::vec4 ray_clipCoordinates = glm::vec4(x, y, -1.0f, 1.0f);
    glm::vec4 ray_eyeCoordinates = glm::inverse(m_camera->m_projection) * ray_clipCoordinates;
    glm::vec4 ray_worldCoordinates = glm::inverse(m_camera->m_view) * glm::vec4(ray_eyeCoordinates.x, ray_eyeCoordinates.y, -1.0f, 0.0f);
    glm::vec3 rayDirection = glm::normalize(glm::vec3(ray_worldCoordinates.x, ray_worldCoordinates.y, ray_worldCoordinates.z));

    m_dot->SetEnabled(false);

    for (const Mesh* mesh : m_meshes)
    {
        glm::vec3 hitPosition;
        glm::vec3 hitNormal;
        bool hit = mesh->HitTest(m_camera->m_position, rayDirection, hitPosition, hitNormal);

        if (!hit)
        {
            continue;
        }

        if (m_dot)
        {
            m_dot->m_position = hitPosition;
            m_dot->SetEnabled(true);
        }
    }
}