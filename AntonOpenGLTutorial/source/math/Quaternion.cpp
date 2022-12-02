#include "Quaternion.h"

#include <algorithm>

Quaternion Quaternion::Identity() noexcept
{
    return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}

Quaternion Quaternion::AngleAxis(float angleInDegrees, const glm::vec3& axis) noexcept
{
    float halfAngle = glm::radians(angleInDegrees) / 2.0f;
    glm::vec3 rotationAxis = sin(halfAngle) * glm::normalize(axis);
    Quaternion q;
    q.w = cos(halfAngle);
    q.x = rotationAxis.x;
    q.y = rotationAxis.y;
    q.z = rotationAxis.z;
    return q;
}

Quaternion Quaternion::Slerp(const Quaternion& q, const Quaternion& r, float t, bool shortestPath) noexcept
{
    t = std::clamp(t, 0.0f, 1.0f);

    float dotProduct = q.DotProduct(r);
    Quaternion s = r;

    if (shortestPath && dotProduct < 0.0f)
    {
        s.Negate();
        dotProduct = q.DotProduct(s);
    }

    float omega = acos(dotProduct);
    float sineOfOmega = sin(omega);

    if (sineOfOmega == 0.0f)
    {
        return (1.0f - t) * q + t * s;
    }

    float a = sin((1.0f - t) * omega) / sineOfOmega;
    float b = sin(t * omega) / sineOfOmega;
    Quaternion result = a * q + b * s;
    return result;
}

Quaternion Quaternion::FromEulerAngles(float rollInDegrees, float pitchInDegrees, float yawInDegrees) noexcept
{
    float rollInRadians = glm::radians(rollInDegrees);
    float pitchInRadians = glm::radians(pitchInDegrees);
    float yawInRadians = glm::radians(yawInDegrees);
    float cr = cos(rollInRadians / 2.0f);
    float sr = sin(rollInRadians / 2.0f);
    float cp = cos(pitchInRadians / 2.0f);
    float sp = sin(pitchInRadians / 2.0f);
    float cy = cos(yawInRadians / 2.0f);
    float sy = sin(yawInRadians / 2.0f);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = cr * sp * cy + sr * cp * sy;
    q.y = cr * cp * sy - sr * sp * cy;
    q.z = sr * cp * cy - cr * sp * sy;
    return q;
}

Quaternion::Quaternion() noexcept
    : w(1.0f)
    , x(0.0f)
    , y(0.0f)
    , z(0.0f)
{
}

Quaternion::Quaternion(float w, float x, float y, float z) noexcept
    : w(w)
    , x(x)
    , y(y)
    , z(z)
{
}

Quaternion Quaternion::operator+(const Quaternion& rhs) const noexcept
{
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const noexcept
{
    float tempW = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    float tempX = w * rhs.x + x * rhs.w - y * rhs.z + z * rhs.y;
    float tempY = w * rhs.y + x * rhs.z + y * rhs.w - z * rhs.x;
    float tempZ = w * rhs.z - x * rhs.y + y * rhs.x + z * rhs.w;
    return Quaternion(tempW, tempX, tempY, tempZ);
}

Quaternion Quaternion::operator*(float scalar) const noexcept
{
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

Quaternion Quaternion::operator/(float scalar) const noexcept
{
    return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
}

void Quaternion::GetAngleAxis(float& angleInDegrees, glm::vec3& axis) const noexcept
{
    float angleInRadians = 2 * acos(w);
    angleInDegrees = glm::degrees(angleInRadians);
    axis.x = x;
    axis.y = y;
    axis.z = z;
    axis = glm::normalize(axis);
}

float Quaternion::GetLength() const noexcept
{
    return sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::Normalize() noexcept
{
    float length = GetLength();

    if (length <= 0.0001f)
    {
        return;
    }

    w /= length;
    x /= length;
    y /= length;
    z /= length;
}

void Quaternion::Negate() noexcept
{
    w = -w;
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::GetNegation() const noexcept
{
    return Quaternion(-w, -x, -y, -z);
}

void Quaternion::Invert()  noexcept
{
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::GetInverse() const noexcept
{
    return Quaternion(w, -x, -y, -z);
}

float Quaternion::DotProduct(const Quaternion& rhs) const noexcept
{
    return w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z;
}

glm::vec3 Quaternion::ToEulerAngles() const noexcept
{
    glm::vec3 angles;

    float a = 2 * (w * x + y * z);
    float b = 1 - 2 * (x * x + y * y);
    angles.x = glm::degrees(atan2(a, b));

    float c = 2 * (w * y - x * z);

    if (fabs(c) >= 1.0f)
    {
        angles.y = std::copysign(90.0f, c);
    }
    else
    {
        angles.y = glm::degrees(asin(c));
    }

    float d = 2 * (w * z + y * x);
    float e = 1 - 2 * (y * y + z * z);
    angles.z = glm::degrees(atan2(d, e));

    return angles;
}

glm::mat4 Quaternion::ToMatrix() const noexcept
{
    glm::mat4 matrix;
    matrix[0][0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
    matrix[0][1] = 2.0f * x * y + 2.0f * w * z;
    matrix[0][2] = 2.0f * x * z - 2.0f * w * y;
    matrix[0][3] = 0.0f;

    matrix[1][0] = 2.0f * x * y - 2.0f * w * z;
    matrix[1][1] = 1.0f - 2.0f * x * x - 2.0f * z * z;
    matrix[1][2] = 2.0f * y * z + 2 * w * x;
    matrix[1][3] = 0.0f;

    matrix[2][0] = 2.0f * x * z + 2.0f * w * y;
    matrix[2][1] = 2.0f * y * z - 2.0f * w * x;
    matrix[2][2] = 1.0f - 2.0f * x * x - 2.0f * y * y;
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;

    return matrix;
}

Quaternion operator*(float scalar, const Quaternion& q) noexcept
{
    return q * scalar;
}