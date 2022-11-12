#include "Sphere.h"

#include <glm/gtc/constants.hpp>

Sphere::Sphere(float radius, int stackCount, int segmentCount)
{
    float stackStep = glm::pi<float>() / stackCount;
    float segmentStep = 2.0f * glm::pi<float>() / segmentCount;

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            float stackAngle = glm::half_pi<float>() - i * stackStep;
            float chordLength = radius * cos(stackAngle);
            float segmentAngle = j * segmentStep;
            float x = chordLength * sin(segmentAngle);
            float y = radius * sin(stackAngle);
            float z = chordLength * cos(segmentAngle);
            glm::vec3 a(x, y, z);

            stackAngle = glm::half_pi<float>() - (i + 1) * stackStep;
            chordLength = radius * cos(stackAngle);
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 b(x, y, z);

            segmentAngle = (j + 1) * segmentStep;
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 c(x, y, z);

            stackAngle = glm::half_pi<float>() - i * stackStep;
            chordLength = radius * cos(stackAngle);
            x = chordLength * sin(segmentAngle);
            y = radius * sin(stackAngle);
            z = chordLength * cos(segmentAngle);
            glm::vec3 d(x, y, z);

            AddAttribute(a, glm::normalize(a));
            AddAttribute(b, glm::normalize(b));
            AddAttribute(c, glm::normalize(c));
            AddAttribute(c, glm::normalize(c));
            AddAttribute(d, glm::normalize(d));
            AddAttribute(a, glm::normalize(a));
        }
    }

    FinalizeGeometry();
}