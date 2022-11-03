#include "Cylinder.h"

#include <glm/ext.hpp>

Cylinder::Cylinder(float height, float radius, int stackCount, int segmentCount)
{
    float angleInRadians = 2.0f * 3.14f / segmentCount;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angleInRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 a(0.0f, height, radius);
    glm::vec3 b(0.0f, 0.0f, radius);

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < segmentCount; j++)
        {
            bool lastAttribute = (i == stackCount - 1 && j == segmentCount - 1);
            glm::vec3 c = glm::vec3(rotation * glm::vec4(a, 1.0f));
            glm::vec3 d = glm::vec3(rotation * glm::vec4(b, 1.0f));
            AddAttribute(a, glm::vec3(a.x, 0.0f, a.z), glm::vec4(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z), glm::vec4(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z), glm::vec4(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));

            AddAttribute(c, glm::vec3(c.x, 0.0f, c.z), glm::vec4(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
            AddAttribute(b, glm::vec3(b.x, 0.0f, b.z), glm::vec4(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f));
            AddAttribute(d, glm::vec3(d.x, 0.0f, d.z), glm::vec4(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec4(1.0f), lastAttribute);

            a = c;
            b = d;
        }
    }
}
