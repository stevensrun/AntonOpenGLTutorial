#include "Cube.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

Cube::Cube()
{
    AddAttribute(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));

    AddAttribute(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    AddAttribute(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));

    for (int i = 1; i <= 3; i++)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(i * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        for (int j = 0; j < 6; j++)
        {
            const glm::vec3& point = m_points[j];
            glm::vec3 rotatedPoint = rotation * glm::vec4(point, 1.0f);
            const glm::vec3& normal = m_normals[j];
            glm::vec3 roatatedNormal = rotation * glm::vec4(normal, 0.0f);
            AddAttribute(rotatedPoint, roatatedNormal);
        }
    }

    for (int i = -1; i <= 1; i++)
    {
        if (i == 0)
        {
            continue;
        }

        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(i * 90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        for (int j = 0; j < 6; j++)
        {
            const glm::vec3& point = m_points[j];
            glm::vec3 rotatedPoint = rotation * glm::vec4(point, 1.0f);
            const glm::vec3& normal = m_normals[j];
            glm::vec3 roatatedNormal = rotation * glm::vec4(normal, 0.0f);
            AddAttribute(rotatedPoint, roatatedNormal);
        }
    }

    FinalizeGeometry();
}