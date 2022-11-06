#include "Cone.h"

#include <glm/ext.hpp>

Cone::Cone(float height, float radius, int stackCount, int segmentCount)
{
    float angleInDegrees = 360.0f / segmentCount;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 a(0.0f, height / 2.0f, 0.0f);
    glm::vec3 b(0.0f, -height / 2.0f, radius);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            bool lastAttribute = (i == stackCount - 1 && j == segmentCount - 1);
            glm::vec3 c = glm::vec3(rotation * glm::vec4(b, 1.0f));
            AddAttribute(a, glm::vec3(a.x, 0.0f, a.z));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z), lastAttribute);

            b = c;
        }
    }
}
