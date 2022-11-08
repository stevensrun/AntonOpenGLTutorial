#include "Mesh.h"
#include "camera/Camera.h"
#include "components/Component.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lights/Light.h"
#include "materials/Material.h"
#include "shaders/ShaderManager.h"

Mesh::Mesh()
    : m_enabled(true)
    , m_material(nullptr)
    , m_normalMaterial(nullptr)
    , m_attributeBuffer(0)
    , m_normalBuffer(0)
    , m_position(0.0f, 0.0f, 0.0f)
{
    glGenVertexArrays(1, &m_attributeVertexArray);
    glBindVertexArray(m_attributeVertexArray);

    glGenVertexArrays(1, &m_normalVertexArray);
    glBindVertexArray(m_normalVertexArray);
}

Mesh::~Mesh()
{
    glBindVertexArray(m_attributeVertexArray);
    glDeleteBuffers(1, &m_attributeBuffer);
    glDeleteVertexArrays(1, &m_attributeVertexArray);

    glBindVertexArray(m_normalVertexArray);
    glDeleteBuffers(1, &m_normalBuffer);
    glDeleteVertexArrays(1, &m_normalVertexArray);
}

void Mesh::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

void Mesh::AddAttribute(const glm::vec3& point, const glm::vec3& normal)
{
    m_points.push_back(point);
    m_normals.push_back(normal);
}

void Mesh::FinalizeGeometry()
{
    std::vector<glm::vec3> attributes;
    std::vector<glm::vec3> normals;

    for (size_t i = 0; i < m_points.size(); i++)
    {
        attributes.push_back(m_points[i]);
        attributes.push_back(m_normals[i]);
        normals.push_back(m_points[i]);
        normals.push_back(m_points[i] + m_normals[i] * 0.15f);
    }

    int stride = 2 * sizeof(glm::vec3);

    glBindVertexArray(m_attributeVertexArray);
    glGenBuffers(1, &m_attributeBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * attributes.size(), attributes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(m_normalVertexArray);
    glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
}

void Mesh::PrepareShader(Material* material, ShaderManager* shaderManager, Camera* camera, Light* light)
{
    if (!material)
    {
        return;
    }

    const std::string& shaderName = material->GetShaderName();
    shaderManager->UseShader(shaderName);
    shaderManager->SetUniform(shaderName, "cameraPosition", 3, glm::value_ptr(camera->m_position));
    shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(camera->m_view));
    shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(camera->m_projection));

    if (light)
    {
        shaderManager->SetUniform(shaderName, "lightPosition", 3, glm::value_ptr(light->m_position));
        shaderManager->SetUniform(shaderName, "ambientLightColor", 3, glm::value_ptr(light->m_ambientColor));
        shaderManager->SetUniform(shaderName, "diffuseLightColor", 3, glm::value_ptr(light->m_diffuseColor));
        shaderManager->SetUniform(shaderName, "specularLightColor", 3, glm::value_ptr(light->m_specularColor));
    }

    shaderManager->SetUniform(shaderName, "ambientReflectivity", 3, glm::value_ptr(material->m_ambientReflectivity));
    shaderManager->SetUniform(shaderName, "diffuseReflectivity", 3, glm::value_ptr(material->m_diffuseReflectivity));
    shaderManager->SetUniform(shaderName, "specularReflectivity", 4, glm::value_ptr(material->m_specularReflectivity));

    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position) * m_rotation.ToMatrix();
    shaderManager->SetUniform(shaderName, "model", 4, 4, false, glm::value_ptr(model));
}

void Mesh::Update(float deltaTimeInSeconds)
{
    for (Component* component : m_components)
    {
        component->Update(deltaTimeInSeconds);
    }
}

void Mesh::Draw(ShaderManager* shaderManager, Camera* camera, Light* light)
{
    if (!m_enabled)
    {
        return;
    }

    PrepareShader(m_material, shaderManager, camera, light);
    glBindVertexArray(m_attributeVertexArray);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_points.size()));
}

void Mesh::DrawNormals(ShaderManager* shaderManager, Camera* camera)
{
    if (!m_enabled)
    {
        return;
    }

    PrepareShader(m_normalMaterial, shaderManager, camera, nullptr);
    glBindVertexArray(m_normalVertexArray);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_LINES, 0, static_cast<int>(m_normals.size() * 2));
}

bool Mesh::HitTest(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& hitPoint, glm::vec3& hitNormal)
{
    return false;
}

void Mesh::AddComponent(Component* component)
{
    component->OnAdded(this);
    m_components.push_back(component);
}