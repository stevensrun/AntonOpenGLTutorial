#include "Quaternion.h"

Quaternion Quaternion::AngleAxis(float radians, glm::vec3 axis)
{
    axis = glm::normalize(axis);

    Quaternion q;
    q.m_w = cos(radians / 2.0f);
    q.m_x = sin(radians / 2.0f) * axis.x;
    q.m_y = sin(radians / 2.0f) * axis.y;
    q.m_z = sin(radians / 2.0f) * axis.z;
    return q;
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
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
        result.m_w = (1.0f - t) * q1.m_w + t * temp.m_w;
        result.m_x = (1.0f - t) * q1.m_x + t * temp.m_x;
        result.m_y = (1.0f - t) * q1.m_y + t * temp.m_y;
        result.m_z = (1.0f - t) * q1.m_z + t * temp.m_z;
        return result;
    }
    
    float a = sin((1.0f - t) * omega) / denominator;
    float b = sin(t * omega) / denominator;

    result.m_w = a * q1.m_w + b * temp.m_w;
    result.m_x = a * q1.m_x + b * temp.m_x;
    result.m_y = a * q1.m_y + b * temp.m_y;
    result.m_z = a * q1.m_z + b * temp.m_z;
    return result;
}

Quaternion Quaternion::Multiply(const Quaternion& q, const Quaternion& r)
{
    float w = r.m_w * q.m_w - r.m_x * q.m_x - r.m_y * q.m_y - r.m_z * q.m_z;
    float x = r.m_w * q.m_x + r.m_x * q.m_w - r.m_y * q.m_z + r.m_z * q.m_y;
    float y = r.m_w * q.m_y + r.m_x * q.m_z + r.m_y * q.m_w - r.m_z * q.m_x;
    float z = r.m_w * q.m_z - r.m_w * q.m_y + r.m_y * q.m_x + r.m_z * q.m_w;
    return Quaternion(w, x, y, z);
}

float Quaternion::DotProduct(const Quaternion& q1, const Quaternion& q2)
{
    return q1.m_x * q2.m_x + q1.m_y * q2.m_y + q1.m_z * q2.m_z + q1.m_w * q2.m_w;
}

float Quaternion::GetRotationAngle(const glm::mat4& matrix)
{
    float trace = matrix[0][0] + matrix[1][1] + matrix[2][2] + matrix[3][3];
    return acos(trace / 2 - 1);
}

glm::vec3 Quaternion::GetRotationAxis(const glm::mat4& matrix, float angleInRadians)
{
    float denominator = 2.0 * sin(angleInRadians);
    float x = (matrix[2][1] - matrix[1][2]) / denominator;
    float y = (matrix[0][2] - matrix[2][0]) / denominator;
    float z = (matrix[1][0] - matrix[0][1]) / denominator;

    return glm::vec3(x, y, z);
}

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
    : m_w(w)
    , m_x(x)
    , m_y(y)
    , m_z(z)
{
}

float Quaternion::GetLength() const
{
    return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

void Quaternion::Normalize()
{
    float length = GetLength();

    if (length <= 0.0001)
    {
        return;
    }

    m_w /= length;
    m_x /= length;
    m_y /= length;
    m_z /= length;
}

void Quaternion::Negate()
{
    m_w = -m_w;
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

glm::mat4 Quaternion::ToMatrix() const
{
    glm::mat4 matrix;
    matrix[0][0] = 1 - 2 * m_y * m_y - 2 * m_z * m_z;
    matrix[0][1] = 2 * m_x * m_y + 2 * m_w * m_z;
    matrix[0][2] = 2 * m_x * m_z - 2 * m_w * m_y;
    matrix[0][3] = 0;

    matrix[1][0] = 2 * m_x * m_y - 2 * m_w * m_z;
    matrix[1][1] = 1 - 2 * m_x * m_x - 2 * m_z * m_z;
    matrix[1][2] = 2 * m_x * m_z + 2 * m_w * m_y;
    matrix[1][3] = 0;

    matrix[2][0] = 2 * m_x * m_z + 2 * m_w * m_y;
    matrix[2][1] = 2 * m_y * m_z - 2 * m_w * m_x;
    matrix[2][2] = 1 - 2 * m_x * m_x - 2 * m_y * m_y;
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

    return matrix;
}

