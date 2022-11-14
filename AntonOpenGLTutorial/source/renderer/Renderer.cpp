#include "Renderer.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera/Camera.h"
#include "lights/Light.h"
#include "materials/Material.h"
#include "meshes/Mesh.h"
#include "scene/Scene.h"
#include "shaders/ShaderManager.h"
#include <stb_image_write.h>

Renderer::Renderer()
    : m_polygonMode(GL_FILL)
    , m_culledFace(GL_BACK)
    , m_isCullingFace(false)
    , m_shaderManager(nullptr)
{
    m_shaderManager = new ShaderManager();
    m_shaderManager->LoadShader("phongShading", "shaders/phongShading.glsl");
    m_shaderManager->LoadShader("blinnPhongShading", "shaders/blinnPhongShading.glsl");
    m_shaderManager->LoadShader("textureMap", "shaders/textureMap.glsl");
    m_shaderManager->LoadShader("ambientReflectivity", "shaders/ambientReflectivity.glsl");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Renderer::~Renderer()
{
    if (m_shaderManager)
    {
        delete m_shaderManager;
        m_shaderManager = nullptr;
    }
}

std::unordered_map<std::string, std::vector<const Mesh*>> Renderer::CreateMeshShaderBatch(const std::vector<Mesh*>& meshes)
{
    std::unordered_map<std::string, std::vector<const Mesh*>> shadersBatch;

    for (const Mesh* mesh : meshes)
    {
        if (!mesh->IsEnabled())
        {
            continue;
        }

        std::string meshShaderName = mesh->m_material->GetShaderName();

        if (shadersBatch.find(meshShaderName) == shadersBatch.end())
        {
            shadersBatch[meshShaderName] = std::vector<const Mesh*>();
        }

        std::vector<const Mesh*>& meshDrawList = shadersBatch[meshShaderName];
        meshDrawList.push_back(mesh);
    }

    return shadersBatch;
}

std::unordered_map<std::string, std::vector<const Mesh*>> Renderer::CreateNormalsShaderBatch(const std::vector<Mesh*>& meshes)
{
    std::unordered_map<std::string, std::vector<const Mesh*>> shadersBatch;
    
    for (const Mesh* mesh : meshes)
    {
        if (!mesh->IsEnabled() || !mesh->m_normalMaterial)
        {
            continue;
        }

        std::string normalsShaderName = mesh->m_normalMaterial->GetShaderName();

        if (shadersBatch.find(normalsShaderName) == shadersBatch.end())
        {
            shadersBatch[normalsShaderName] = std::vector<const Mesh*>();
        }

        std::vector<const Mesh*>& normalsDrawList = shadersBatch[normalsShaderName];
        normalsDrawList.push_back(mesh);
    }

    return shadersBatch;
}

void Renderer::Draw(Scene* scene)
{
    std::vector<Mesh*> meshes = scene->GetMeshes();
    std::unordered_map<std::string, std::vector<const Mesh*>> meshShadersBatch = CreateMeshShaderBatch(meshes);
    std::unordered_map<std::string, std::vector<const Mesh*>> normalsShadersBatch = CreateNormalsShaderBatch(meshes);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);

    if (m_isCullingFace)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(m_culledFace);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    Camera* camera = scene->GetCamera();
    const std::vector<Light*>& lights = scene->GetLights();

    for (const std::pair<std::string, std::vector<const Mesh*>>& batch : meshShadersBatch)
    {
        std::string shaderName = batch.first;
        m_shaderManager->UseShader(shaderName);

        if (camera)
        {
            m_shaderManager->SetUniform(shaderName, "cameraPosition", 3, glm::value_ptr(camera->m_position));
            m_shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(camera->m_view));
            m_shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(camera->m_projection));
        }

        for (Light* light : lights)
        {
            m_shaderManager->SetUniform(shaderName, "lightPosition", 3, glm::value_ptr(light->m_position));
            m_shaderManager->SetUniform(shaderName, "ambientLightColor", 3, glm::value_ptr(light->m_ambientColor));
            m_shaderManager->SetUniform(shaderName, "diffuseLightColor", 3, glm::value_ptr(light->m_diffuseColor));
            m_shaderManager->SetUniform(shaderName, "specularLightColor", 3, glm::value_ptr(light->m_specularColor));
        }

        for (const Mesh* mesh : batch.second)
        {
            mesh->Draw(m_shaderManager);
        }
    }

    for (const std::pair<std::string, std::vector<const Mesh*>>& batch : normalsShadersBatch)
    {
        std::string shaderName = batch.first;
        m_shaderManager->UseShader(shaderName);

        if (camera)
        {
            m_shaderManager->SetUniform(shaderName, "cameraPosition", 3, glm::value_ptr(camera->m_position));
            m_shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(camera->m_view));
            m_shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(camera->m_projection));
        }

        for (const Mesh* mesh : batch.second)
        {
            mesh->DrawNormals(m_shaderManager);
        }
    }
}

bool Renderer::TakeScreenshot(const std::string& filepath, int width, int height) const
{
    int bitsPerPixel = 3;
    unsigned char* buffer = new unsigned char[width * height * bitsPerPixel];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
    stbi_flip_vertically_on_write(true);
    int success = stbi_write_png(filepath.c_str(), width, height, bitsPerPixel, buffer, width * bitsPerPixel);
    return (success == 1);
}