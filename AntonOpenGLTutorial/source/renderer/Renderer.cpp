#include "Renderer.h"
#include "camera/SceneCamera.h"
#include "camera/UiCamera.h"
#include "gizmos/Gizmo.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "lights/Light.h"
#include "materials/Material.h"
#include "memory/MemoryTracker.h"
#include "meshes/BasicMesh.h"
#include "meshes/Mesh.h"
#include "scene/Scene.h"
#include "shaders/ShaderManager.h"
#include <stb_image_write.h>

Renderer::Renderer(GLFWwindow* window)
    : m_polygonMode(GL_FILL)
    , m_culledFace(GL_BACK)
    , m_isCullingFace(false)
    , m_drawNormals(false)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

Renderer::~Renderer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

std::unordered_map<std::string, std::vector<std::shared_ptr<BasicMesh>>> Renderer::CreateMeshShaderBatch(const std::vector<std::shared_ptr<BasicMesh>>& meshes)
{
    std::unordered_map<std::string, std::vector<std::shared_ptr<BasicMesh>>> shadersBatch;

    for (const std::shared_ptr<BasicMesh>& mesh : meshes)
    {
        if (!mesh->IsEnabled())
        {
            continue;
        }

        std::string meshShaderName = mesh->m_material->GetShaderName();

        if (shadersBatch.find(meshShaderName) == shadersBatch.end())
        {
            shadersBatch[meshShaderName] = std::vector<std::shared_ptr<BasicMesh>>();
        }

        std::vector<std::shared_ptr<BasicMesh>>& meshDrawList = shadersBatch[meshShaderName];
        meshDrawList.push_back(mesh);
    }

    return shadersBatch;
}

std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> Renderer::CreateNormalsShaderBatch(const std::vector<std::shared_ptr<BasicMesh>>& meshes)
{
    std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> shadersBatch;

    for (const std::shared_ptr<BasicMesh>& basicMesh : meshes)
    {
        if (!basicMesh->IsEnabled())
        {
            continue;
        }

        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(basicMesh);

        if (!mesh || !mesh->m_normalMaterial)
        {
            continue;
        }

        std::string normalsShaderName = mesh->m_normalMaterial->GetShaderName();

        if (shadersBatch.find(normalsShaderName) == shadersBatch.end())
        {
            shadersBatch[normalsShaderName] = std::vector<std::shared_ptr<Mesh>>();
        }

        std::vector<std::shared_ptr<Mesh>>& normalsDrawList = shadersBatch[normalsShaderName];
        normalsDrawList.push_back(mesh);
    }

    return shadersBatch;
}

void Renderer::Draw(Scene* scene)
{
    std::vector<std::shared_ptr<BasicMesh>> meshes = scene->GetMeshes();
    std::unordered_map<std::string, std::vector<std::shared_ptr<BasicMesh>>> meshShadersBatch = CreateMeshShaderBatch(meshes);
    std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> normalsShadersBatch = CreateNormalsShaderBatch(meshes);

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

    std::shared_ptr<ShaderManager>& shaderManager = scene->GetShaderManager();
    std::shared_ptr <SceneCamera>& camera = scene->GetSceneCamera();
    const std::vector<std::shared_ptr<Light>>& lights = scene->GetLights();

    for (const std::pair<std::string, std::vector<std::shared_ptr<BasicMesh>>>& batch : meshShadersBatch)
    {
        std::string shaderName = batch.first;
        shaderManager->UseShader(shaderName);

        if (camera)
        {
            glm::vec3 position = camera->GetPosition();
            glm::mat4 view = camera->GetView();
            glm::mat4 projection = camera->GetProjection();
            shaderManager->SetUniform(shaderName, "cameraPosition", 3, glm::value_ptr(position));
            shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(view));
            shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(projection));
        }

        for (const std::shared_ptr<Light>& light : lights)
        {
            shaderManager->SetUniform(shaderName, "lightPosition", 3, glm::value_ptr(light->m_position));
            shaderManager->SetUniform(shaderName, "ambientLightColor", 3, glm::value_ptr(light->m_ambientColor));
            shaderManager->SetUniform(shaderName, "diffuseLightColor", 3, glm::value_ptr(light->m_diffuseColor));
            shaderManager->SetUniform(shaderName, "specularLightColor", 3, glm::value_ptr(light->m_specularColor));
        }

        for (const std::shared_ptr<BasicMesh>& mesh : batch.second)
        {
            mesh->Draw(shaderManager);
        }
    }

    for (const std::pair<std::string, std::vector<std::shared_ptr<Mesh>>>& batch : normalsShadersBatch)
    {
        std::string shaderName = batch.first;
        shaderManager->UseShader(shaderName);

        if (camera)
        {
            glm::vec3 position = camera->GetPosition();
            glm::mat4 view = camera->GetView();
            glm::mat4 projection = camera->GetProjection();
            shaderManager->SetUniform(shaderName, "cameraPosition", 3, glm::value_ptr(position));
            shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(view));
            shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(projection));
        }

        for (const std::shared_ptr<Mesh>& mesh : batch.second)
        {
            mesh->DrawNormals(shaderManager);
        }
    }

    DrawGizmos(scene);
    DrawImGui();
}

void Renderer::DrawGizmos(Scene* scene)
{
    glDisable(GL_DEPTH_TEST);

    std::shared_ptr<ShaderManager>& shaderManager = scene->GetShaderManager();
    std::shared_ptr<UiCamera>& camera = scene->GetUiCamera();

    for (const std::shared_ptr<Gizmo>& gizmo : scene->GetGizmos())
    {
        std::string shaderName = gizmo->m_material->GetShaderName();
        shaderManager->UseShader(shaderName);

        if (camera)
        {
            glm::mat4 view = camera->GetView();
            glm::mat4 projection = camera->GetProjection();
            shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(view));
            shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(projection));
        }

        gizmo->Draw(shaderManager);
    }
}

void Renderer::DrawImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Text("Memory Usage (bytes): %d", MemoryTracker::GetMemoryUsage(MemoryCategory::Meshes));

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Renderer::TakeScreenshot(const std::string& filepath, int width, int height) const
{
    int bytesPerPixel = 3;
    unsigned char* buffer = new unsigned char[width * height * bytesPerPixel];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
    stbi_flip_vertically_on_write(true);
    int success = stbi_write_png(filepath.c_str(), width, height, bytesPerPixel, buffer, width * bytesPerPixel);
    return (success == 1);
}