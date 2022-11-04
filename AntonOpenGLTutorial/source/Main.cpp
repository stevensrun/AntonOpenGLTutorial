#include "components/Rotator.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include "math/Quaternion.h"
#include "meshes/Cone.h"
#include "meshes/Cylinder.h"
#include "meshes/Dot.h"
#include "meshes/Mesh.h"
#include "meshes/Plane.h"
#include "meshes/Triangle.h"
#include "shaders/ShaderManager.h"
#include <string>

struct Light
{
    glm::vec3 position;
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
};

struct Camera
{
    glm::vec3 position;
    glm::vec3 rotation;
    float moveSpeed;
    float rotationSpeed;
    glm::mat4 view;
    glm::mat4 projection;
};

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
    glm::vec4 ray_eye = glm::inverse(camera->projection) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
    glm::vec4 tempRay = glm::inverse(camera->view) * ray_eye;
    glm::vec3 ray_world(tempRay.x, tempRay.y, tempRay.z);
    ray_world = glm::normalize(ray_world);

    dot->SetEnabled(false);

    for (Mesh* mesh : meshes)
    {
        glm::vec3 hitPoint;
        glm::vec3 hitNormal;
        bool hit = mesh->HitTest(camera->position, ray_world, hitPoint, hitNormal);

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

    Camera* camera = new Camera { glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 45.0f, glm::mat4(1.0f), glm::mat4(1.0f) };
    camera->view = glm::lookAt(camera->position, camera->rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    camera->projection = glm::perspective(glm::radians(67.0f), 1280.0f / 760.0f, 0.1f, 100.0f);

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

    Light light(glm::vec3(2.0f, 2.0f, 1.0f), glm::vec3(0.0f, 0.2f, 0.2f), glm::vec3(0.75f, 0.5f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f));

    Cone* cone = new Cone(1.0f, 0.5f, 1, 24);
    cone->m_position = glm::vec3(-2.0f, 0.0f, 0.0f);
    meshes.push_back(cone);

    Cylinder* cylinder = new Cylinder(1.0f, 0.5f, 1, 24);
    cylinder->AddComponent(new Rotator(135.0f, glm::vec3(1.0, 1.0f, 0.0f)));
    meshes.push_back(cylinder);

    Plane* plane = new Plane();
    plane->m_position = glm::vec3(2.0f, 0.0f, 0.0f);
    meshes.push_back(plane);

    Triangle* triangle = new Triangle();
    triangle->m_position = glm::vec3(4.0f, 0.0f, 0.0f);
    meshes.push_back(triangle);

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

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderManager.UseShader("phongShading");
        shaderManager.SetUniform("phongShading", "view", 4, 4, false, glm::value_ptr(camera->view));
        shaderManager.SetUniform("phongShading", "projection", 4, 4, false, glm::value_ptr(camera->projection));
        shaderManager.SetUniform("phongShading", "lightPosition", 3, glm::value_ptr(light.position));
        shaderManager.SetUniform("phongShading", "ambientLightColor", 3, glm::value_ptr(light.ambientColor));
        shaderManager.SetUniform("phongShading", "diffuseLightColor", 3, glm::value_ptr(light.diffuseColor));

        for (Mesh* mesh : meshes)
        {
            mesh->Update(elapsedSeconds);

            glm::mat4 translation = glm::translate(glm::mat4(1.0f), mesh->m_position);
            glm::mat4 model = translation * mesh->m_rotation.ToMatrix();
            shaderManager.SetUniform("phongShading", "model", 4, 4, false, glm::value_ptr(model));

            mesh->Draw();
        }

        glDisable(GL_DEPTH_TEST);
        dot->Update(elapsedSeconds);
        dot->Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        bool cameraMoved = false;

        if (glfwGetKey(window, GLFW_KEY_A))
        {
            camera->position.x -= camera->moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_D))
        {
            camera->position.x += camera->moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_PAGE_UP))
        {
            camera->position.y += camera->moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
        {
            camera->position.y -= camera->moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_W))
        {
            camera->position.z -= camera->moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_S))
        {
            camera->position.z += camera->moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {
            camera->rotation.y += camera->rotationSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            camera->rotation.y -= camera->rotationSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (cameraMoved)
        {
            glm::vec3 center = glm::rotateY(glm::vec3(0.0, 0.0, -1.0), glm::radians(camera->rotation.y)) + camera->position;
            camera->view = glm::lookAt(camera->position, center, glm::vec3(0.0, 1.0, 0.0));
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }

    glfwTerminate();

    return 0;
}