#include "Torus.h"
#include <glm/gtc/constants.hpp>

Torus::Torus(float majorRadius, float minorRadius, int stackCount, int segmentCount)
{
    float stackStep = 2.0f * glm::pi<float>() / stackCount;
    float segmentStep = 2.0f * glm::pi<float>() / segmentCount;
    int firstElementIndex = 0;

    for (int i = 0; i < segmentCount; i++)
    {
        for (int j = 0; j < stackCount; j++)
        {
            float segmentAngle = i * segmentStep;
            float stackAngle = j * stackStep;
            float x = (majorRadius + minorRadius * cos(stackAngle)) * sin(segmentAngle);
            float y = minorRadius * sin(stackAngle);
            float z = (majorRadius + minorRadius * cos(stackAngle)) * cos(segmentAngle);
            glm::vec3 a(x, y, z);
            glm::vec3 normalA(minorRadius * cos(stackAngle) * sin(segmentAngle), minorRadius * sin(stackAngle), minorRadius * cos(stackAngle) * cos(segmentAngle));

            segmentAngle = (i + 1) * segmentStep;
            stackAngle = (j + 1) * stackStep;
            x = (majorRadius + minorRadius * cos(stackAngle)) * sin(segmentAngle);
            y = minorRadius * sin(stackAngle);
            z = (majorRadius + minorRadius * cos(stackAngle)) * cos(segmentAngle);
            glm::vec3 b(x, y, z);
            glm::vec3 normalB(minorRadius * cos(stackAngle) * sin(segmentAngle), minorRadius * sin(stackAngle), minorRadius * cos(stackAngle) * cos(segmentAngle));

            segmentAngle = i * segmentStep;
            stackAngle = (j + 1) * stackStep;
            x = (majorRadius + minorRadius * cos(stackAngle)) * sin(segmentAngle);
            y = minorRadius * sin(stackAngle);
            z = (majorRadius + minorRadius * cos(stackAngle)) * cos(segmentAngle);
            glm::vec3 c(x, y, z);
            glm::vec3 normalC(minorRadius * cos(stackAngle) * sin(segmentAngle), minorRadius * sin(stackAngle), minorRadius * cos(stackAngle) * cos(segmentAngle));

            segmentAngle = (i + 1) * segmentStep;
            stackAngle = j * stackStep;
            x = (majorRadius + minorRadius * cos(stackAngle)) * sin(segmentAngle);
            y = minorRadius * sin(stackAngle);
            z = (majorRadius + minorRadius * cos(stackAngle)) * cos(segmentAngle);
            glm::vec3 d(x, y, z);
            glm::vec3 normalD(minorRadius * cos(stackAngle) * sin(segmentAngle), minorRadius * sin(stackAngle), minorRadius * cos(stackAngle) * cos(segmentAngle));

            AddAttribute(a, normalA);
            AddAttribute(b, normalB);
            AddAttribute(c, normalC);
            AddAttribute(d, normalD);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 1);
            AddElementIndex(firstElementIndex + 2);
            AddElementIndex(firstElementIndex);
            AddElementIndex(firstElementIndex + 3);
            AddElementIndex(firstElementIndex + 1);
            firstElementIndex += 4;
        }
    }

    FinalizeGeometry();
}