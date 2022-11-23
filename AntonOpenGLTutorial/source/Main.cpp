#include "camera/SceneCamera.h"
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/Renderer.h"
#include "scene/Scene.h"

void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void MousePositionCallback(GLFWwindow* window, double xPosition, double yPosition);

double previousXPosition = 1280.0f / 2.0;
double previousYPosition = 760.0 / 2.0;

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit() failed\n";
        return 1;
    }

    int width = 1280;
    int height = 760;
    glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "glfwCreateWindow() failed\n";
        glfwTerminate();
        return 1;
    }

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MousePositionCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "glewInit() failed\n";
        glfwTerminate();
        return 1;
    }

    Renderer* renderer = new Renderer(window);
    Scene* scene = new Scene();
    std::pair<Renderer*, Scene*> pair = std::make_pair(renderer, scene);
    glfwSetWindowUserPointer(window, &pair);

    scene->Setup(width, height);
    SceneCamera* camera = scene->GetSceneCamera();
    double previousSeconds = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera->MoveForward();
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera->MoveBackward();
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera->MoveLeft();
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera->MoveRight();
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            camera->MoveDown();
        }
        else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            camera->MoveUp();
        }

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
    std::pair<Renderer*, Scene*>* pair = static_cast<std::pair<Renderer*, Scene*>*>(glfwGetWindowUserPointer(window));
    Scene* scene = pair->second;

    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        int width;
        int height;
        glfwGetWindowSize(window, &width, &height);
        scene->OnMouseClick(static_cast<float>(mouseX), static_cast<float>(mouseY), width, height);
    }
    else if (button == GLFW_MOUSE_BUTTON_2)
    {
        SceneCamera* camera = scene->GetSceneCamera();

        if (action == GLFW_PRESS)
        {
            camera->SetAllowCameraMovement(true);
            glfwGetCursorPos(window, &previousXPosition, &previousYPosition);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, MousePositionCallback);
        }
        else
        {
            camera->SetAllowCameraMovement(false);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, nullptr);
        }
    }
}

void MousePositionCallback(GLFWwindow* window, double xPosition, double yPosition)
{
    double deltaX = xPosition - previousXPosition;
    double deltaY = yPosition - previousYPosition;
    previousXPosition = xPosition;
    previousYPosition = yPosition;

    std::pair<Renderer*, Scene*>* pair = static_cast<std::pair<Renderer*, Scene*>*>(glfwGetWindowUserPointer(window));
    Scene* scene = pair->second;
    SceneCamera* camera = scene->GetSceneCamera();
    camera->Yaw(static_cast<float>(deltaX));
    camera->Pitch(static_cast<float>(deltaY));
}