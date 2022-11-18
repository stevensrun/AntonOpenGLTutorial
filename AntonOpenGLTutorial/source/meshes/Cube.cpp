#include "Cube.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Cube::Cube(int stackCount, int segmentCount)
{
    float stackStep = 1.0f / stackCount;
    float segmentStep = 1.0f / segmentCount;
    glm::vec3 normal(0.0f, 0.0f, 1.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f + j * segmentStep;
            float y = 0.5f - i * stackStep;
            float z = 0.5f;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f - i * stackStep;
            z = 0.5f;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(c, normal);
            AddAttribute(b, normal);
            AddAttribute(d, normal);
        }
    }

    normal = glm::vec3(1.0f, 0.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = 0.5f;
            float y = 0.5f - i * stackStep;
            float z = 0.5f - j * segmentStep;
            glm::vec3 a(x, y, z);

            x = 0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f - j * segmentStep;
            glm::vec3 b(x, y, z);

            x = 0.5f;
            y = 0.5f - i * stackStep;
            z = 0.5f - (j + 1) * segmentStep;
            glm::vec3 c(x, y, z);

            x = 0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = 0.5f - (j + 1) * segmentStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(c, normal);
            AddAttribute(b, normal);
            AddAttribute(d, normal);
        }
    }

    normal = glm::vec3(0.0f, 0.0f, -1.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = 0.5f - j * segmentStep;
            float y = 0.5f - i * stackStep;
            float z = -0.5f;
            glm::vec3 a(x, y, z);

            x = 0.5f - j * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f;
            glm::vec3 b(x, y, z);

            x = 0.5f - (j + 1) * segmentStep;
            y = 0.5f - i * stackStep;
            z = -0.5f;
            glm::vec3 c(x, y, z);

            x = 0.5f - (j + 1) * segmentStep;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(c, normal);
            AddAttribute(b, normal);
            AddAttribute(d, normal);
        }
    }

    normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f;
            float y = 0.5f - i * stackStep;
            float z = -0.5f + j * segmentStep;
            glm::vec3 a(x, y, z);

            x = -0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f + j * segmentStep;
            glm::vec3 b(x, y, z);

            x = -0.5f;
            y = 0.5f - i * stackStep;
            z = -0.5f + (j + 1) * segmentStep;
            glm::vec3 c(x, y, z);

            x = -0.5f;
            y = 0.5f - (i + 1) * stackStep;
            z = -0.5f + (j + 1) * segmentStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(c, normal);
            AddAttribute(b, normal);
            AddAttribute(d, normal);
        }
    }

    normal = glm::vec3(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f + j * segmentStep;
            float y = 0.5f;
            float z = -0.5f + i * stackStep;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * segmentStep;
            y = 0.5f;
            z = -0.5f + (i + 1) * stackStep;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f;
            z = -0.5f + i * stackStep;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = 0.5f;
            z = -0.5f + (i + 1) * stackStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(c, normal);
            AddAttribute(b, normal);
            AddAttribute(d, normal);
        }
    }

    normal = glm::vec3(0.0f, -1.0f, 0.0f);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float x = -0.5f + j * segmentStep;
            float y = -0.5f;
            float z = 0.5f - i * stackStep;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * segmentStep;
            y = -0.5f;
            z = 0.5f - (i + 1) * stackStep;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = -0.5f;
            z = 0.5f - i * stackStep;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * segmentStep;
            y = -0.5f;
            z = 0.5f - (i + 1) * stackStep;
            glm::vec3 d(x, y, z);

            AddAttribute(a, normal);
            AddAttribute(b, normal);
            AddAttribute(c, normal);
            AddAttribute(c, normal);
            AddAttribute(b, normal);
            AddAttribute(d, normal);
        }
    }

    FinalizeGeometry();
}