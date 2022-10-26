#pragma once

#include "Mesh.h"

class Triangle : public Mesh
{
public:
    Triangle();
    virtual ~Triangle() = default;

    virtual bool HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal) override;
    virtual void AddAttribute(const glm::vec4& point, const glm::vec4& color, bool lastAttribute = false) override;
    virtual void Update(float deltaTimeInSeconds) override;
    virtual void Draw() override;

private:
    void UpdateNormal();
    std::vector<glm::vec4> GetTransformedPoints();

private:
    glm::vec3 m_normal;
    float m_t;
};