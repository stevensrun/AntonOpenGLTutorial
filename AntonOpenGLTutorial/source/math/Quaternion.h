#pragma once

#include <glm/glm.hpp>

/*
* To rotate using a quaternion we need to first get a delta rotation with AngleAxis(). Then we need to convert the quaternion to a 4x4 matrix which we then use to transform the points as normal.
* glm::mat4 is column major so the the entries are indexed as [column][row]
*/

class Quaternion final
{
public:
    static Quaternion Identity() noexcept;
    static Quaternion AngleAxis(float angleInDegrees, const glm::vec3& axis) noexcept;
    static Quaternion Slerp(const Quaternion& q, const Quaternion& r, float t, bool shortestPath = true) noexcept;
    static Quaternion FromEulerAngles(float rollInDegrees, float pitchInDegrees, float yawInDegrees) noexcept;

    Quaternion() noexcept;
    Quaternion(float w, float x, float y, float z) noexcept;
    ~Quaternion() = default;

    Quaternion operator+(const Quaternion& rhs) const noexcept;
    Quaternion operator*(const Quaternion& rhs) const noexcept;
    Quaternion operator*(float scalar) const noexcept;
    Quaternion operator/(float scalar) const noexcept;

    void GetAngleAxis(float& angle, glm::vec3& axis) const noexcept;
    float GetLength() const noexcept;
    void Normalize() noexcept;
    void Negate() noexcept;
    Quaternion GetNegation() const noexcept;
    void Invert() noexcept;
    Quaternion GetInverse() const noexcept;
    float DotProduct(const Quaternion& rhs) const noexcept;
    glm::vec3 ToEulerAngles() const noexcept;
    glm::mat4 ToMatrix() const noexcept;

public:
    float w;
    float x;
    float y;
    float z;
};

Quaternion operator*(float scalar, const Quaternion& q) noexcept;