#include "Quaternion.h"

Quaternion Quaternion::AngleAxis(float radians, glm::vec3 axis)
{
    axis = glm::normalize(axis);

    Quaternion q;
    q.w = cos(radians / 2.0f);
    q.x = sin(radians / 2.0f) * axis.x;
    q.y = sin(radians / 2.0f) * axis.y;
    q.z = sin(radians / 2.0f) * axis.z;
    return q;
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    if (t < 0.0)
    {
        t = 0.0;
    }

    if (t > 1.0)
    {
        t = 1.0;
    }

    Quaternion temp = q2;
    float dotProduct = DotProduct(q1, temp);

    if (dotProduct < 0.0)
    {
        temp.Negate();
        dotProduct = DotProduct(q1, temp);
    }

    if (abs(dotProduct) >= 1.0)
    {
        return q1;
    }

    float omega = acos(dotProduct);
    float denominator = sin(omega);
    Quaternion result;

    if (abs(denominator) < 0.001)
    {
        result.w = (1.0f - t) * q1.w + t * temp.w;
        result.x = (1.0f - t) * q1.x + t * temp.x;
        result.y = (1.0f - t) * q1.y + t * temp.y;
        result.z = (1.0f - t) * q1.z + t * temp.z;
        return result;
    }
    
    float a = sin((1.0f - t) * omega) / denominator;
    float b = sin(t * omega) / denominator;

    result.w = a * q1.w + b * temp.w;
    result.x = a * q1.x + b * temp.x;
    result.y = a * q1.y + b * temp.y;
    result.z = a * q1.z + b * temp.z;
    return result;
}

Quaternion Quaternion::Multiply(const Quaternion& q, const Quaternion& r)
{
    float w = r.w * q.w - r.x * q.x - r.y * q.y - r.z * q.z;
    float x = r.w * q.x + r.x * q.w - r.y * q.z + r.z * q.y;
    float y = r.w * q.y + r.x * q.z + r.y * q.w - r.z * q.x;
    float z = r.w * q.z - r.w * q.y + r.y * q.x + r.z * q.w;
    return Quaternion(w, x, y, z);
}

float Quaternion::DotProduct(const Quaternion& q1, const Quaternion& q2)
{
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

float Quaternion::GetRotationAngle(const glm::mat4& matrix)
{
    float trace = matrix[0][0] + matrix[1][1] + matrix[2][2] + matrix[3][3];
    return acos(trace / 2 - 1);
}

glm::vec3 Quaternion::GetRotationAxis(const glm::mat4& matrix, float angleInRadians)
{
    float denominator = 2.0 * sin(angleInRadians);
    float x = (matrix[1][2] - matrix[2][1]) / denominator;
    float y = (matrix[2][0] - matrix[0][2]) / denominator;
    float z = (matrix[0][1] - matrix[1][0]) / denominator;

    return glm::vec3(x, y, z);
}

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
    : w(w)
    , x(x)
    , y(y)
    , z(z)
{
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

