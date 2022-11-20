#include "SlerpComponent.h"
#include "meshes/BasicMesh.h"

SlerpComponent::SlerpComponent(const Quaternion& q, const Quaternion& r, float step, bool shortestPath)
    : m_t(0.0f)
    , m_q(q)
    , m_r(r)
    , m_step(step)
    , m_shortestPath(shortestPath)
{
}

void SlerpComponent::Update(float deltaTimeInSeconds)
{
    m_t += m_step;
    m_mesh->m_rotation = Quaternion::Slerp(m_q, m_r, m_t, m_shortestPath);
}