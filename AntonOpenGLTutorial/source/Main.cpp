#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <fstream>
#include <iostream>
#include "math/Quaternion.h"
#include "meshes/Dot.h"
#include "meshes/Mesh.h"
#include "meshes/Triangle.h"
#include "shaders/ShaderManager.h"
#include <sstream>
#include <string>
#include <unordered_map>

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

void CursorPosCallback(GLFWwindow* window, double x, double y)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    float tempX = (2.0f * static_cast<float>(x)) / width - 1.0f;
    float tempY = 1.0f - (2.0f * static_cast<float>(y)) / height;
    float tempZ = 1.0f;
    glm::vec3 ray_nds(tempX, tempY, tempZ);
    glm::vec4 ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
    glm::vec4 ray_eye = glm::inverse(camera->projection) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
    glm::vec4 tempRay = glm::inverse(camera->view) * ray_eye;
    glm::vec3 ray_world(tempRay.x, tempRay.y, tempRay.z);
    ray_world = glm::normalize(ray_world);

    for (Mesh* mesh : meshes)
    {
        float t = mesh->GetIntersectionParameter(camera->position, ray_world);

        if (t <= 0.0f)
        {
            continue;
        }

        glm::vec3 hitPoint = camera->position + ray_world * t;
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

    Camera* camera = new Camera { glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 45.0f, glm::mat4(1.0f), glm::mat4(1.0f) };

    glfwSetWindowUserPointer(window, camera);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << __FUNCTION__ << " glewInit() failed\n";
        glfwTerminate();
        return 1;
    }

    camera->view = glm::lookAt(camera->position, camera->rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    camera->projection = glm::perspective(glm::radians(67.0f), 1280.0f / 760.0f, 0.1f, 100.0f);

    ShaderManager shaderManager;
    shaderManager.LoadShader("interpolatedColor", "shaders/interpolatedColor.glsl");
    shaderManager.LoadShader("dynamicColor", "shaders/dynamicColor.glsl");

    Triangle* triangle = new Triangle();
    triangle->AddAttribute(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    triangle->AddAttribute(glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    triangle->AddAttribute(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), true);
    meshes.push_back(triangle);

    Quaternion q = Quaternion::AngleAxis(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Quaternion r = Quaternion::AngleAxis(glm::radians(225.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    float t = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        static double previousSeconds = glfwGetTime();
        double currentSeconds = glfwGetTime();
        float elapsedSeconds = static_cast<float>(currentSeconds - previousSeconds);
        previousSeconds = currentSeconds;

        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        t += 0.001f;
        Quaternion s = Quaternion::Slerp(q, r, t);
        glm::mat4 model = s.ToMatrix();

        shaderManager.UseShader("interpolatedColor");
        shaderManager.SetUniform("interpolatedColor", "model", 4, 4, false, glm::value_ptr(model));
        shaderManager.SetUniform("interpolatedColor", "view", 4, 4, false, glm::value_ptr(camera->view));
        shaderManager.SetUniform("interpolatedColor", "projection", 4, 4, false, glm::value_ptr(camera->projection));
        
        for (Mesh* mesh : meshes)
        {
            mesh->Draw();
        }

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