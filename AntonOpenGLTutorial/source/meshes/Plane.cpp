#include "Plane.h"

Plane::Plane(int rows, int columns)
{
    float rowStep = 1.0f / rows;
    float columnStep = 1.0f / columns;
    glm::vec3 normal(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            float x = -0.5f + j * columnStep;
            float y = 0.0f;
            float z = -0.5f + i * rowStep;
            glm::vec3 a(x, y, z);

            x = -0.5f + j * columnStep;
            y = 0.0f;
            z = -0.5f + (i + 1) * rowStep;
            glm::vec3 b(x, y, z);

            x = -0.5f + (j + 1) * columnStep;
            y = 0.0f;
            z = -0.5f + i * rowStep;
            glm::vec3 c(x, y, z);

            x = -0.5f + (j + 1) * columnStep;
            y = 0.0f;
            z = -0.5f + (i + 1) * rowStep;
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