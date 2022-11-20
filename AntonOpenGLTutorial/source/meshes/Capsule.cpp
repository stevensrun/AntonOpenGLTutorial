#include "Capsule.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Capsule::Capsule(float height, float radius, int stackCount, int segmentCount)
{
    glm::vec3 hemisphereOffset = glm::vec3(0.0f, height / 2.0f, 0.0f);
    float hemisphereStackCount = 4;
    float hemisphereStackStep = glm::half_pi<float>() / hemisphereStackCount;
    float segmentStep = 2.0f * glm::pi<float>() / segmentCount;

    for (int i = 0; i < hemisphereStackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float stackAngle = glm::half_pi<float>() - i * hemisphereStackStep;
            float chordLength = radius * cos(stackAngle);
            float segmentAngle = j * segmentStep;
            float x = chordLength * sin(segmentAngle);
            float y = radius * sin(stackAngle);
            float z = chordLength * cos(segmentAngle);
            glm::vec3 a(x, y, z);

            stackAngle = glm::half_pi<float>() - (i + 1) * hemisphereStackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = j * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            stackAngle = glm::half_pi<float>() - i * hemisphereStackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            stackAngle = glm::half_pi<float>() - (i + 1) * hemisphereStackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 d(x, y, z);

            AddAttribute(a + hemisphereOffset, a);
            AddAttribute(b + hemisphereOffset, b);
            AddAttribute(c + hemisphereOffset, c);
            AddAttribute(c + hemisphereOffset, c);
            AddAttribute(b + hemisphereOffset, b);
            AddAttribute(d + hemisphereOffset, d);
        }
    }

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float segmentAngle = j * segmentStep;
            float x = radius * sin(segmentAngle);
            float y = hemisphereOffset.y;
            float z = radius * cos(segmentAngle);
            glm::vec3 a(x, y, z);

            segmentAngle = j * segmentStep;
            x = radius * sin(segmentAngle);
            y = -hemisphereOffset.y;
            z = radius * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            segmentAngle = (j + 1) * segmentStep;
            x = radius * sin(segmentAngle);
            y = hemisphereOffset.y;
            z = radius * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            segmentAngle = (j + 1) * segmentStep;
            x = radius * sin(segmentAngle);
            y = -hemisphereOffset.y;
            z = radius * cos(segmentAngle);
            glm::vec3 d(x, y, z);

            AddAttribute(a, glm::vec3(a.x, 0.0f, a.z));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z));
            AddAttribute(d, glm::vec3(d.x, 0.0f, d.z));
        }
    }

    for (int i = 0; i < hemisphereStackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float stackAngle = -glm::half_pi<float>() + i * hemisphereStackStep;
            float chordLength = radius * cos(stackAngle);
            float segmentAngle = j * segmentStep;
            float x = chordLength * sin(segmentAngle);
            float y = radius * sin(stackAngle);
            float z = chordLength * cos(segmentAngle);
            glm::vec3 a(x, y, z);

            stackAngle = -glm::half_pi<float>() + (i + 1) * hemisphereStackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            stackAngle = -glm::half_pi<float>() + (i + 1) * hemisphereStackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = j * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            stackAngle = -glm::half_pi<float>() + i * hemisphereStackStep;
            chordLength = radius * cos(stackAngle);
            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 d(x, y, z);

            AddAttribute(a - hemisphereOffset, a);
            AddAttribute(b - hemisphereOffset, b);
            AddAttribute(c - hemisphereOffset, c);
            AddAttribute(b - hemisphereOffset, b);
            AddAttribute(a - hemisphereOffset, a);
            AddAttribute(d - hemisphereOffset, d);
        }
    }

    FinalizeGeometry();
}