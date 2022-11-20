#pragma once

class BasicMesh;

class Component
{
public:
    Component();
    virtual ~Component() = default;

    virtual void OnAdded(BasicMesh* mesh);
    virtual void OnRemoved();
    virtual void Update(float delaTimeInSeconds) = 0;

protected:
    BasicMesh* m_mesh;
};