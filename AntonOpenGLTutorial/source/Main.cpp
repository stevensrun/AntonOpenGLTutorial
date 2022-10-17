#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <fstream>
#include <iostream>
#include "shader/ShaderManager.h"
#include <sstream>
#include <string>
#include <unordered_map>

void ErrorCallback(int errorCode, const char* errorMessage)
{
    std::cerr << __FUNCTION__ << " " << errorMessage << "\n";
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        std::cerr << __FUNCTION__ << " glfwInit() failed\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cerr << __FUNCTION__ << " glfwCreateWindow() failed\n";
        glfwTerminate();
        return 1;
    }

    struct Camera
    {
        glm::vec3 position;
        glm::vec3 rotation;
        float moveSpeed;
        float rotationSpeed;
    };

    Camera camera {
        glm::vec3(0.0, 0.0, 2.0),
        glm::vec3(0.0, 0.0, 0.0),
        1.0,
        45.0
    };

    glfwSetWindowSizeCallback(window, WindowSizeCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << __FUNCTION__ << " glewInit() failed\n";
        glfwTerminate();
        return 1;
    }

    glm::vec3 positions[] = {
        { 0.0, 0.5, 0.0 },
        { 0.5, -0.5, 0.0 },
        { -0.5, -0.5, 0.0 },
    };

    glm::vec3 colors[] = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 },
    };

    glm::vec3 normal = glm::normalize(glm::cross(positions[0], positions[1])) * 0.25f;

    glm::vec3 arrowPositions[] = {
        {0.0, 0.0, 0.0},
        { normal }
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int positionVbo;
    glGenBuffers(1, &positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    unsigned int colorVbo;
    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    unsigned int arrowVao;
    glGenVertexArrays(1, &arrowVao);
    glBindVertexArray(arrowVao);

    unsigned int arrowVbo;
    glGenBuffers(1, &arrowVbo);
    glBindBuffer(GL_ARRAY_BUFFER, arrowVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arrowPositions), arrowPositions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    ShaderManager shaderManager;
    shaderManager.LoadShader("interpolatedColor", "shaders/interpolatedColor.glsl");
    shaderManager.LoadShader("dynamicColor", "shaders/dynamicColor.glsl");

    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 view = glm::lookAt(camera.position, camera.rotation, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(glm::radians(67.0), 1280.0 / 760.0, 0.1, 100.0);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        static double previousSeconds = glfwGetTime();
        double currentSeconds = glfwGetTime();
        float elapsedSeconds = static_cast<float>(currentSeconds - previousSeconds);
        previousSeconds = currentSeconds;

        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderManager.UseShader("interpolatedColor");
        shaderManager.SetUniform("interpolatedColor", "model", 4, 4, false, glm::value_ptr(model));
        shaderManager.SetUniform("interpolatedColor", "view", 4, 4, false, glm::value_ptr(view));
        shaderManager.SetUniform("interpolatedColor", "projection", 4, 4, false, glm::value_ptr(projection));
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glm::vec4 arrowColor(1.0, 1.0, 1.0, 1.0);
        shaderManager.UseShader("dynamicColor");
        shaderManager.SetUniform("dynamicColor", "model", 4, 4, false, glm::value_ptr(model));
        shaderManager.SetUniform("dynamicColor", "view", 4, 4, false, glm::value_ptr(view));
        shaderManager.SetUniform("dynamicColor", "projection", 4, 4, false, glm::value_ptr(projection));
        shaderManager.SetUniform("dynamicColor", "u_color", 4, glm::value_ptr(arrowColor));
        glBindVertexArray(arrowVao);
        glLineWidth(8.0);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();

        bool cameraMoved = false;

        if (glfwGetKey(window, GLFW_KEY_A))
        {
            camera.position.x -= camera.moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_D))
        {
            camera.position.x += camera.moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_PAGE_UP))
        {
            camera.position.y += camera.moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
        {
            camera.position.y -= camera.moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_W))
        {
            camera.position.z -= camera.moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_S))
        {
            camera.position.z += camera.moveSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {
            camera.rotation.y += camera.rotationSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            camera.rotation.y -= camera.rotationSpeed * elapsedSeconds;
            cameraMoved = true;
        }

        if (cameraMoved)
        {
            glm::vec3 center = glm::rotateY(glm::vec3(0.0, 0.0, -1.0), glm::radians(camera.rotation.y)) + camera.position;
            view = glm::lookAt(camera.position, center, glm::vec3(0.0, 1.0, 0.0));
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }

    glfwTerminate();

    return 0;
}