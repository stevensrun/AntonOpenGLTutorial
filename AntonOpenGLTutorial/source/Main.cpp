#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/Renderer.h"
#include "scene/Scene.h"

void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit() failed\n";
        return 1;
    }

    glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "glfwCreateWindow() failed\n";
        glfwTerminate();
        return 1;
    }

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "glewInit() failed\n";
        glfwTerminate();
        return 1;
    }

    Renderer* renderer = new Renderer();
    Scene* scene = new Scene();
    std::pair<Renderer*, Scene*> pair = std::make_pair(renderer, scene);
    glfwSetWindowUserPointer(window, &pair);

    scene->Setup();
    double previousSeconds = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double currentSeconds = glfwGetTime();
        float deltaSeconds = static_cast<float>(currentSeconds - previousSeconds);
        previousSeconds = currentSeconds;
        scene->Update(deltaSeconds);
        renderer->Draw(scene);
        glfwSwapBuffers(window);
        glfwPollEvents();
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

    std::pair<Renderer*, Scene*>* pair = static_cast<std::pair<Renderer*, Scene*>*>(glfwGetWindowUserPointer(window));
    Renderer* renderer = pair->first;

    if (keyCode == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (keyCode == GLFW_KEY_F1)
    {
        if (renderer->m_polygonMode == GL_FILL)
        {
            renderer->m_polygonMode = GL_LINE;
        }
        else
        {
            renderer->m_polygonMode = GL_FILL;
        }
    }
    else if (keyCode == GLFW_KEY_F2)
    {
        renderer->m_isCullingFace = !renderer->m_isCullingFace;
    }
    else if (keyCode == GLFW_KEY_F3)
    {
        if (renderer->m_culledFace == GL_FRONT)
        {
            renderer->m_culledFace = GL_BACK;
        }
        else
        {
            renderer->m_culledFace = GL_FRONT;
        }
    }
    else if (keyCode == GLFW_KEY_F11)
    {
        int width;
        int height;
        glfwGetWindowSize(window, &width, &height);
        unsigned long long seconds = duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::stringstream ss;
        ss << "screenshots/screenshot_" << seconds << ".png";
        bool success = renderer->TakeScreenshot(ss.str(), width, height);

        if (!success)
        {
            std::cerr << "Failed to create screenshot image: " << ss.str() << "\n";
        }
    }
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action != GLFW_PRESS || button != GLFW_MOUSE_BUTTON_LEFT)
    {
        return;
    }

    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    std::pair<Renderer*, Scene*>* pair = static_cast<std::pair<Renderer*, Scene*>*>(glfwGetWindowUserPointer(window));
    Scene* scene = pair->second;
    scene->OnMouseClick(static_cast<float>(mouseX), static_cast<float>(mouseY), width, height);
}