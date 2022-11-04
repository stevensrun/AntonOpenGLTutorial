#pragma once

class Mesh;

class Component
{
public:
    Component();
    virtual ~Component() = default;

    virtual void OnAdded(Mesh* mesh);
    virtual void OnRemoved();
    virtual void Update(float delaTimeInSeconds) = 0;

protected:
    Mesh* m_mesh;
};