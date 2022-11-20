#pragma once

#include <glm/glm.hpp>

/*
* To rotate using a quaternion we need to first get a delta rotation with AngleAxis(). Then we need to convert the quaternion to a 4x4 matrix which we then use to transform the points as normal.
* glm::mat4 is column major so the the entries are indexed as [column][row]
*/

class Quaternion
{
public:
    friend Quaternion operator*(float scalar, const Quaternion& q);

    static Quaternion Identity();
    static Quaternion AngleAxis(float angleInDegrees, const glm::vec3& axis);
    static Quaternion Slerp(const Quaternion& q, const Quaternion& r, float t, bool shortestPath = true);
    static Quaternion FromEulerAngles(float rollInDegrees, float pitchInDegrees, float yawInDegrees);

    Quaternion();
    Quaternion(float w, float x, float y, float z);
    ~Quaternion() = default;

    Quaternion operator+(const Quaternion& rhs) const;
    Quaternion operator*(const Quaternion& rhs) const;
    Quaternion operator*(float scalar) const;
    Quaternion operator/(float scalar) const;

    void GetAngleAxis(float& angle, glm::vec3& axis) const;
    float GetLength() const;
    void Normalize();
    void Negate();
    Quaternion GetNegation() const;
    void Invert();
    Quaternion GetInverse() const;
    float DotProduct(const Quaternion& rhs) const;
    glm::vec3 ToEulerAngles() const;
    glm::mat4 ToMatrix() const;

public:
    float w;
    float x;
    float y;
    float z;
};
