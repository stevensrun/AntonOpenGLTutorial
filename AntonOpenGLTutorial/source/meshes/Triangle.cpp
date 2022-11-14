#include "Triangle.h"

Triangle::Triangle()
{
    AddAttribute(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    AddAttribute(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    AddAttribute(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0, 0.0, 1.0f));
    FinalizeGeometry();
}