#include "Mesh.h"
#include "camera/Camera.h"
#include "components/Component.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lights/Light.h"
#include "materials/Material.h"
#include "math/Quaternion.h"
#include "shaders/ShaderManager.h"

Mesh::Mesh()
    : m_enabled(true)
    , m_material(nullptr)
    , m_normalMaterial(nullptr)
    , m_attributeBuffer(0)
    , m_normalBuffer(0)
    , m_textureId(-1)
    , m_position(0.0f, 0.0f, 0.0f)
    , m_scale(1.0f, 1.0f, 1.0f)
{
    m_rotation = Quaternion::AngleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
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

void Mesh::AddAttribute(const glm::vec3& point, const glm::vec3& normal, const glm::vec2& textureCoordinate)
{
    m_points.push_back(point);
    m_normals.push_back(normal);
    m_textureCoordinates.push_back(textureCoordinate);
}

void Mesh::FinalizeGeometry()
{
    std::vector<float> attributes;
    std::vector<float> normals;

    for (size_t i = 0; i < m_points.size(); i++)
    {
        attributes.push_back(m_points[i].x);
        attributes.push_back(m_points[i].y);
        attributes.push_back(m_points[i].z);
        attributes.push_back(m_normals[i].x);
        attributes.push_back(m_normals[i].y);
        attributes.push_back(m_normals[i].z);

        if (m_textureCoordinates.size() > 0)
        {
            attributes.push_back(m_textureCoordinates[i].s);
            attributes.push_back(m_textureCoordinates[i].t);
        }

        normals.push_back(m_points[i].x);
        normals.push_back(m_points[i].y);
        normals.push_back(m_points[i].z);

        glm::vec3 endPoint = m_points[i] + m_normals[i] * 0.15f;
        normals.push_back(endPoint.x);
        normals.push_back(endPoint.y);
        normals.push_back(endPoint.z);
    }

    int stride = (m_textureCoordinates.size() > 0) ? 8 * sizeof(float) : 6 * sizeof(float);
    glBindVertexArray(m_attributeVertexArray);
    glGenBuffers(1, &m_attributeBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * attributes.size(), attributes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    if (m_textureCoordinates.size() > 0)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, false, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindVertexArray(m_normalVertexArray);
    glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
}

void Mesh::PrepareShader(Material* material, ShaderManager* shaderManager, Camera* camera, Light* light)
{
    if (!material)
    {
        return;
    }

    if (m_textureId == -1)
    {
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);

        if (material->GetTextureChannelCount() == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, material->GetTextureWidth(), material->GetTextureHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, material->GetBaseTextureData());
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, material->GetTextureWidth(), material->GetTextureHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, material->GetBaseTextureData());
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

    int textureSlot = material->GetTextureSlot();
    shaderManager->SetUniform(shaderName, "baseTexture", 1, &textureSlot);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position) * m_rotation.ToMatrix() * glm::scale(glm::mat4(1.0f), m_scale);
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
    if (!m_enabled || !m_material)
    {
        return;
    }

    PrepareShader(m_material, shaderManager, camera, light);
    glBindVertexArray(m_attributeVertexArray);

    if (m_material->GetTextureSlot() != -1)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glActiveTexture(GL_TEXTURE0 + m_material->GetTextureSlot());
    }

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_points.size()));
}

void Mesh::DrawNormals(ShaderManager* shaderManager, Camera* camera)
{
    if (!m_enabled || !m_normalMaterial)
    {
        return;
    }

    PrepareShader(m_normalMaterial, shaderManager, camera, nullptr);
    glBindVertexArray(m_normalVertexArray);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.0f);
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