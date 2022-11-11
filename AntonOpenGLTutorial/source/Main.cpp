#include "camera/Camera.h"
#include "components/Rotator.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
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
#include "shaders/ShaderManager.h"
#include <stb_image.h>
#include <string>

void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

std::vector<Mesh*> meshes;
Dot* dot = nullptr;

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cerr << __FUNCTION__ << " glfwInit() failed\n";
        return 1;
    }

    glfwWindowHint(GLFW_SAMPLES, 16);
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cerr << __FUNCTION__ << " glfwCreateWindow() failed\n";
        glfwTerminate();
        return 1;
    }

    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    
    glfwSetWindowUserPointer(window, camera);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << __FUNCTION__ << " glewInit() failed\n";
        glfwTerminate();
        return 1;
    }

    Light* light = new Light(glm::vec3(0.0f, 0.0f, 3.0f));
    light->m_ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    light->m_diffuseColor = glm::vec3(0.7f, 0.7f, 0.7f);
    light->m_specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

    ShaderManager* shaderManager = new ShaderManager();
    shaderManager->LoadShader("phongShading", "shaders/phongShading.glsl");
    shaderManager->LoadShader("textureMap", "shaders/textureMap.glsl");
    shaderManager->LoadShader("ambientReflectivity", "shaders/ambientReflectivity.glsl");

    Material* normalMaterial = new Material("ambientReflectivity");
    normalMaterial->AddUniform("ambientReflectivity", glm::vec3(1.0f, 0.0f, 0.0f));

    Material* material = new Material("phongShading");
    material->AddUniform("ambientReflectivity", glm::vec3(1.0f, 1.0f, 1.0f));
    material->AddUniform("diffuseReflectivity", glm::vec3(1.0f, 0.5f, 0.0f));
    material->AddUniform("specularReflectivity", glm::vec4(1.0f, 1.0f, 1.0f, 300.0f));

    Material* textureMaterial = new Material("textureMap");

    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channelCount;
    unsigned char* skullData = stbi_load("textures/skulluvmap.png", &width, &height, &channelCount, 0);
    textureMaterial->AddTextureUniform("baseTexture", skullData, width, height, channelCount, 1);
    unsigned char* sandstoneData = stbi_load("textures/sandstone.png", &width, &height, &channelCount, 0);
    textureMaterial->AddTextureUniform("secondaryTexture", sandstoneData, width, height, channelCount, 0);

    Plane* skullPlane = new Plane();
    skullPlane->m_material = textureMaterial;
    skullPlane->m_normalMaterial = normalMaterial;
    skullPlane->m_rotation = Quaternion::AngleAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    meshes.push_back(skullPlane);

    Sphere* sphere = new Sphere(1.0f, 16, 32);
    sphere->m_material = material;
    sphere->m_normalMaterial = normalMaterial;
    sphere->m_position = glm::vec3(-2.0f, 0.0f, 0.0f);
    meshes.push_back(sphere);

    Material* dotMaterial = new Material("ambientReflectivity");
    dotMaterial->AddUniform("ambientReflectivity", glm::vec3(0.0f, 1.0f, 0.0f));

    dot = new Dot();
    dot->m_material = dotMaterial;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        static double previousSeconds = glfwGetTime();
        double currentSeconds = glfwGetTime();
        float elapsedSeconds = static_cast<float>(currentSeconds - previousSeconds);
        previousSeconds = currentSeconds;

        camera->Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Mesh* mesh : meshes)
        {
            mesh->Update(elapsedSeconds);
            mesh->Draw(shaderManager, camera, light);
            mesh->DrawNormals(shaderManager, camera);
        }
        
        dot->Draw(shaderManager, camera, light);
        
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_A))
        {
            camera->m_position.x -= camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_D))
        {
            camera->m_position.x += camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_Q))
        {
            camera->m_position.y += camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_E))
        {
            camera->m_position.y -= camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_W))
        {
            camera->m_position.z -= camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_S))
        {
            camera->m_position.z += camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {
            camera->m_rotation.y += camera->m_rotationSpeedInDegreesPerSecond * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            camera->m_rotation.y -= camera->m_rotationSpeedInDegreesPerSecond * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }

    glfwTerminate();

    return 0;
}

void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        return;
    }

    if (keyCode == GLFW_KEY_F1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (keyCode == GLFW_KEY_F2)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (keyCode == GLFW_KEY_F3)
    {
        glEnable(GL_CULL_FACE);
    }
    else if (keyCode == GLFW_KEY_F4)
    {
        glDisable(GL_CULL_FACE);
    }
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action != GLFW_PRESS)
    {
        return;
    }

    if (button != GLFW_MOUSE_BUTTON_LEFT)
    {
        return;
    }

    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    float tempX = 2.0f * static_cast<float>(x) / width - 1.0f;
    float tempY = 1.0f - 2.0f * static_cast<float>(y) / height;
    glm::vec3 ray_nds(tempX, tempY, 0.0f);
    glm::vec4 ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    glm::vec4 ray_eye = glm::inverse(camera->m_projection) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
    glm::vec4 tempRay = glm::inverse(camera->m_view) * ray_eye;
    glm::vec3 ray_world(tempRay.x, tempRay.y, tempRay.z);
    ray_world = glm::normalize(ray_world);

    dot->SetEnabled(false);

    for (Mesh* mesh : meshes)
    {
        glm::vec3 hitPoint;
        glm::vec3 hitNormal;
        bool hit = mesh->HitTest(camera->m_position, ray_world, hitPoint, hitNormal);

        if (!hit)
        {
            continue;
        }

        dot->m_position = hitPoint;
        dot->SetEnabled(true);
    }
}