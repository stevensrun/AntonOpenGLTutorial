#include "Component.h"

Component::Component()
    : m_mesh(nullptr)
{
}

void Component::OnAdded(BasicMesh* mesh)
{
    m_mesh = mesh;
}

void Component::OnRemoved()
{
    m_mesh = nullptr;
}