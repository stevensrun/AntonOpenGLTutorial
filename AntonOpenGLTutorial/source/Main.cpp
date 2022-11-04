#include "camera/Camera.h"
#include "components/Rotator.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include "lights/Light.h"
#include "math/Quaternion.h"
#include "meshes/Cone.h"
#include "meshes/Cube.h"
#include "meshes/Cylinder.h"
#include "meshes/Dot.h"
#include "meshes/Mesh.h"
#include "meshes/Plane.h"
#include "meshes/Triangle.h"
#include "shaders/ShaderManager.h"
#include <string>

std::vector<Mesh*> meshes;
Dot* dot = nullptr;

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

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cerr << __FUNCTION__ << " glfwInit() failed\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cerr << __FUNCTION__ << " glfwCreateWindow() failed\n";
        glfwTerminate();
        return 1;
    }

    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
    
    glfwSetWindowUserPointer(window, camera);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << __FUNCTION__ << " glewInit() failed\n";
        glfwTerminate();
        return 1;
    }

    Light light(glm::vec3(0.0f, 3.0f, 2.0f));
    light.m_ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    light.m_diffuseColor = glm::vec3(0.7f, 0.7f, 0.7f);
    light.m_specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

    Cone* cone = new Cone(1.0f, 0.5f, 1, 24);
    cone->m_position = glm::vec3(-2.0f, 0.0f, 0.0f);
    meshes.push_back(cone);

    Cube* cube = new Cube();
    cube->AddComponent(new Rotator(135.0f, glm::vec3(0.0f, 1.0f, 1.0f)));
    meshes.push_back(cube);

    Cylinder* cylinder = new Cylinder(1.0f, 0.5f, 1, 24);
    cylinder->m_position = glm::vec3(2.0f, 0.0f, 0.0f);
    cylinder->AddComponent(new Rotator(135.0f, glm::vec3(1.0f, 1.0f, 0.0f)));
    meshes.push_back(cylinder);


    dot = new Dot();

    ShaderManager shaderManager;
    shaderManager.LoadShader("phongShading", "shaders/phongShading.glsl");

    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        static double previousSeconds = glfwGetTime();
        double currentSeconds = glfwGetTime();
        float elapsedSeconds = static_cast<float>(currentSeconds - previousSeconds);
        previousSeconds = currentSeconds;

        camera->Update();

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderManager.UseShader("phongShading");
        shaderManager.SetUniform("phongShading", "view", 4, 4, false, glm::value_ptr(camera->m_view));
        shaderManager.SetUniform("phongShading", "projection", 4, 4, false, glm::value_ptr(camera->m_projection));
        shaderManager.SetUniform("phongShading", "lightPosition", 3, glm::value_ptr(light.m_position));
        shaderManager.SetUniform("phongShading", "ambientLightColor", 3, glm::value_ptr(light.m_ambientColor));
        shaderManager.SetUniform("phongShading", "diffuseLightColor", 3, glm::value_ptr(light.m_diffuseColor));

        for (Mesh* mesh : meshes)
        {
            mesh->Update(elapsedSeconds);
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), mesh->m_position);
            glm::mat4 model = translation* mesh->m_rotation.ToMatrix();
            shaderManager.SetUniform("phongShading", "model", 4, 4, false, glm::value_ptr(model));
            mesh->Draw();
        }

        glDisable(GL_DEPTH_TEST);
        dot->Update(elapsedSeconds);
        dot->Draw();

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

        if (glfwGetKey(window, GLFW_KEY_PAGE_UP))
        {
            camera->m_position.y += camera->m_moveSpeedInSeconds * elapsedSeconds;
        }

        if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
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