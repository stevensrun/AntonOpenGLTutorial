#include "Quaternion.h"

#include <algorithm>

Quaternion Quaternion::Identity()
{
    return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}


Quaternion Quaternion::AngleAxis(float radians, const glm::vec3& axis)
{
    float halfAngle = radians / 2.0f;
    glm::vec3 rotationAxis = sin(halfAngle) * glm::normalize(axis);
    Quaternion q;
    q.w = cos(halfAngle);
    q.x = rotationAxis.x;
    q.y = rotationAxis.y;
    q.z = rotationAxis.z;
    return q;
}

Quaternion Quaternion::Slerp(const Quaternion& q, const Quaternion& r, float t)
{
    t = std::clamp(t, 0.0f, 1.0f);

    float dotProduct = DotProduct(q, r);

    if (abs(dotProduct) >= 1.0f)
    {
        return q;
    }

    float omega = acos(dotProduct);
    float sineOfOmega = sin(omega);
    Quaternion result;
    float oneMinusT = (1.0f - t);

    if (abs(sineOfOmega) < 0.001f)
    {
        result.w = oneMinusT * q.w + t * r.w;
        result.x = oneMinusT * q.x + t * r.x;
        result.y = oneMinusT * q.y + t * r.y;
        result.z = oneMinusT * q.z + t * r.z;
        return result;
    }
    
    float a = sin(oneMinusT * omega) / sineOfOmega;
    float b = sin(t * omega) / sineOfOmega;

    result.w = a * q.w + b * r.w;
    result.x = a * q.x + b * r.x;
    result.y = a * q.y + b * r.y;
    result.z = a * q.z + b * r.z;
    return result;
}

Quaternion Quaternion::Multiply(const Quaternion& q, const Quaternion& r)
{
    float w = q.w * r.w - q.x * r.x - q.y * r.y - q.z * r.z;
    float x = q.w * r.x + q.x * r.w - q.y * r.z + q.z * r.y;
    float y = q.w * r.y + q.x * r.z + q.y * r.w - q.z * r.x;
    float z = q.w * r.z - q.x * r.y + q.y * r.x + q.z * r.w;
    return Quaternion(w, x, y, z);
}

float Quaternion::DotProduct(const Quaternion& q, const Quaternion& r)
{
    return q.w * r.w + q.x * r.x + q.y * r.y + q.z * r.z;
}

float Quaternion::GetRotationAngle(const glm::mat4& matrix)
{
    float trace = matrix[0][0] + matrix[1][1] + matrix[2][2] + matrix[3][3];
    return acos(trace / 2 - 1);
}

glm::vec3 Quaternion::GetRotationAxis(const glm::mat4& matrix, float angleInRadians)
{
    float denominator = 2.0f * sin(angleInRadians);
    float x = (matrix[1][2] - matrix[2][1]) / denominator;
    float y = (matrix[2][0] - matrix[0][2]) / denominator;
    float z = (matrix[0][1] - matrix[1][0]) / denominator;

    return glm::vec3(x, y, z);
}

Quaternion::Quaternion()
    : w(0.0)
    , x(0.0)
    , y(0.0)
    , z(0.0)
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
    : w(w)
    , x(x)
    , y(y)
    , z(z)
{
}

Quaternion Quaternion::operator*(const Quaternion& rhs)
{
    return Quaternion::Multiply(*this, rhs);
}

float Quaternion::GetLength() const
{
    return sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::Normalize()
{
    float length = GetLength();

    if (length <= 0.0001)
    {
        return;
    }

    w /= length;
    x /= length;
    y /= length;
    z /= length;
}

void Quaternion::Negate()
{
    w = -w;
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::Negation()
{
    return Quaternion(-w, -x, -y, -z);
}

void Quaternion::Invert()
{
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::Inverse()
{
    return Quaternion(w, -x, -y, -z);
}

glm::mat4 Quaternion::ToMatrix() const
{
    glm::mat4 matrix;
    matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
    matrix[0][1] = 2 * x * y + 2 * w * z;
    matrix[0][2] = 2 * x * z - 2 * w * y;
    matrix[0][3] = 0;

    matrix[1][0] = 2 * x * y - 2 * w * z;
    matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
    matrix[1][2] = 2 * y * z + 2 * w * x;
    matrix[1][3] = 0;

    matrix[2][0] = 2 * x * z + 2 * w * y;
    matrix[2][1] = 2 * y * z - 2 * w * x;
    matrix[2][2] = 1 - 2 * x * x - 2 * y * y;
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

    return matrix;
}

