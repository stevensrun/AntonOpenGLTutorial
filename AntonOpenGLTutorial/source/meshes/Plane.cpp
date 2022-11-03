#include "Plane.h"

Plane::Plane()
{
    AddAttribute(glm::vec3(-0.5f, 1.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
    AddAttribute(glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
    AddAttribute(glm::vec3(0.5f, 1.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
    AddAttribute(glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
    AddAttribute(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
    AddAttribute(glm::vec3(0.5f, 1.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f), true);
}