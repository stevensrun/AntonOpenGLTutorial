#pragma once

#include "Component.h"
#include "math/Quaternion.h"

class SlerpComponent : public Component
{
public:
    SlerpComponent(const Quaternion& q, const Quaternion& r, float step, bool shortestPath);
    virtual ~SlerpComponent() = default;

    virtual void Update(float delaTimeInSeconds) override;

private:
    float m_t;
    Quaternion m_q;
    Quaternion m_r;
    float m_step;
    bool m_shortestPath;
};