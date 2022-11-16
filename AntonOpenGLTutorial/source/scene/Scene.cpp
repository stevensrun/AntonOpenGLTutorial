#include "Scene.h"
#include "camera/Camera.h"
#include "collisionShapes/TriangleShape.h"
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
    Light* light = new Light(glm::vec3(1.0f, 2.0f, 2.0f));
    light->m_ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    light->m_diffuseColor = glm::vec3(0.7f, 0.7f, 0.7f);
    light->m_specularColor = glm::vec3(0.4f, 0.2f, 0.7f);
    m_lights.push_back(light);
}

void Scene::SetupMeshes()
{
    Material* normalMaterial = new Material("ambientReflectivity");
    normalMaterial->AddUniform("ambientReflectivity", glm::vec3(1.0f, 0.0f, 0.0f));

    Material* pinkPlastic = new Material("phongShading");
    pinkPlastic->AddUniform("ambientReflectivity", glm::vec3(0.2f, 0.2f, 0.2f));
    pinkPlastic->AddUniform("diffuseReflectivity", glm::vec3(1.0f, 0.7f, 1.0f));
    pinkPlastic->AddUniform("specularReflectivity", glm::vec4(0.7f, 0.7f, 0.7f, 200.0f));

    Material* purplePlastic = new Material("phongShading");
    purplePlastic->AddUniform("ambientReflectivity", glm::vec3(0.2f, 0.2f, 0.2f));
    purplePlastic->AddUniform("diffuseReflectivity", glm::vec3(1.0f, 0.0f, 1.0f));
    purplePlastic->AddUniform("specularReflectivity", glm::vec4(1.0f, 1.0f, 1.0f, 200.0f));

    Material* darkPlastic = new Material("blinnPhongShading");
    darkPlastic->AddUniform("ambientReflectivity", glm::vec3(0.2f, 0.2f, 0.2f));
    darkPlastic->AddUniform("diffuseReflectivity", glm::vec3(0.3f, 0.3f, 0.3f));
    darkPlastic->AddUniform("specularReflectivity", glm::vec4(1.0f, 1.0f, 1.0f, 400.0f));

    Cone* cone = new Cone(1.0f, 0.5f, 16, 32);
    cone->m_material = pinkPlastic;
    cone->m_position = glm::vec3(-2.0f, 0.0f, 0.0f);
    cone->m_rotation = Quaternion::AngleAxis(-90.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    m_meshes.push_back(cone);

    Cube* cube = new Cube();
    cube->m_material = purplePlastic;
    cube->m_rotation = Quaternion::AngleAxis(50.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    m_meshes.push_back(cube);

    Sphere* sphere = new Sphere(0.5f, 16, 32);
    sphere->m_material = pinkPlastic;
    sphere->m_position = glm::vec3(2.0f, 0.0f, 0.0f);
    m_meshes.push_back(sphere);

    Plane* plane = new Plane();
    plane->m_material = darkPlastic;
    plane->m_position = glm::vec3(0.0f, -1.0f, 0.0f);
    plane->m_scale = glm::vec3(8.0f, 1.0f, 4.0f);
    m_meshes.push_back(plane);

    Material* colorMaterial = new Material("ambientReflectivity");
    colorMaterial->AddUniform("ambientReflectivity", glm::vec3(0.0f, 1.0f, 0.0f));

    m_dot = new Dot();
    m_dot->m_material = colorMaterial;
    m_dot->m_normalMaterial = normalMaterial;
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

    for (int i = static_cast<int>(m_meshes.size()) - 1; i >= 0; i--)
    {
        TriangleShape* shape = dynamic_cast<TriangleShape*>(m_meshes[i]);

        if (!shape)
        {
            continue;
        }

        m_meshes.erase(m_meshes.begin() + i);
    }

    TriangleShape* shape = nullptr;
    m_dot->SetEnabled(false);

    for (int i = static_cast<int>(m_meshes.size()) - 1; i >= 0; i--)
    {
        const Mesh* mesh = m_meshes[i];
        glm::vec3 hitPosition;
        glm::vec3 hitNormal;
        bool hit = mesh->HitTest(shape, m_camera->m_position, rayDirection, hitPosition, hitNormal);

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
            Material* colorMaterial = new Material("ambientReflectivity");
            colorMaterial->AddUniform("ambientReflectivity", glm::vec3(0.0f, 1.0f, 1.0f));
            shape->m_material = colorMaterial;
            m_meshes.push_back(shape);
        }

        break;
    }

}