#pragma once

#include <glm/glm.hpp>

/*
* To rotate using a quaternion we need to first get a delta rotation with AngleAxis(). Then we need to convert the quaternion to a 4x4 matrix which we then use to transform the points as normal.
*/

class Quaternion
{
public:
    static Quaternion AngleAxis(float radians, glm::vec3 axis);
    static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
    static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
    static float DotProduct(const Quaternion& q1, const Quaternion& q2);
    static float GetRotationAngle(const glm::mat4& matrix);
    static glm::vec3 GetRotationAxis(const glm::mat4& matrix, float angleInRadians);

    Quaternion();
    Quaternion(float w, float x, float y, float z);
    ~Quaternion() = default;

    float GetLength() const;
    void Normalize();
    void Negate();
    glm::mat4 ToMatrix() const;

public:
    float m_w;
    float m_x;
    float m_y;
    float m_z;
};
