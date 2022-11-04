#include "Rotator.h"
#include "math/Quaternion.h"
#include "meshes/Mesh.h"
#include <iostream>

Rotator::Rotator(float angleInDegrees, const glm::vec3& axis)
    : m_currentAngleInDegrees(0.0f)
    , m_angleInDegrees(angleInDegrees)
    , m_axis(axis)
{
}

void Rotator::Update(float delaTimeInSeconds)
{
    m_currentAngleInDegrees += m_angleInDegrees * delaTimeInSeconds;
    m_mesh->m_rotation = Quaternion::AngleAxis(glm::radians(m_currentAngleInDegrees), m_axis);
}