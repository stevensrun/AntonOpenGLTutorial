#pragma once

#include "Component.h"

#include <glm/glm.hpp>

class Rotator : public Component
{
public:
    Rotator(float angleInDegrees, const glm::vec3& axis);
    virtual ~Rotator() = default;

    virtual void Update(float delaTimeInSeconds) override;

private:
    float m_currentAngleInDegrees;
    float m_angleInDegrees;
    glm::vec3 m_axis;
};