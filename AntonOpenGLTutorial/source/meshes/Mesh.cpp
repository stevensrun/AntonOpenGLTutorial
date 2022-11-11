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
    , m_attributesBuffer(0)
    , m_normalsBuffer(0)
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
    glDeleteBuffers(1, &m_attributesBuffer);
    glDeleteVertexArrays(1, &m_attributeVertexArray);

    glBindVertexArray(m_normalVertexArray);
    glDeleteBuffers(1, &m_normalsBuffer);
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
    AddAttribute(point, normal);
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

        glm::vec3 endPoint = m_points[i] + m_normals[i] * 0.1f;
        normals.push_back(endPoint.x);
        normals.push_back(endPoint.y);
        normals.push_back(endPoint.z);
    }

    int stride = (m_textureCoordinates.size() == 0) ? 6 * sizeof(float) : 8 * sizeof(float);
    glBindVertexArray(m_attributeVertexArray);
    glGenBuffers(1, &m_attributesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_attributesBuffer);
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
    glGenBuffers(1, &m_normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalsBuffer);
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

    if (m_textureIds.empty())
    {
        for (const std::pair<std::string, Texture>& pair : material->GetTextureUniforms())
        {
            unsigned int textureId;
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            const Texture& texture = pair.second;
            int format = (texture.m_channelCount == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, texture.m_width, texture.m_height, 0, format, GL_UNSIGNED_BYTE, texture.m_data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            m_textureIds.push_back(textureId);
        }
    }

    const std::string& shaderName = material->GetShaderName();
    shaderManager->UseShader(shaderName);

    if (camera)
    {
        shaderManager->SetUniform(shaderName, "cameraPosition", 3, glm::value_ptr(camera->m_position));
        shaderManager->SetUniform(shaderName, "view", 4, 4, false, glm::value_ptr(camera->m_view));
        shaderManager->SetUniform(shaderName, "projection", 4, 4, false, glm::value_ptr(camera->m_projection));
    }

    if (light)
    {
        shaderManager->SetUniform(shaderName, "lightPosition", 3, glm::value_ptr(light->m_position));
        shaderManager->SetUniform(shaderName, "ambientLightColor", 3, glm::value_ptr(light->m_ambientColor));
        shaderManager->SetUniform(shaderName, "diffuseLightColor", 3, glm::value_ptr(light->m_diffuseColor));
        shaderManager->SetUniform(shaderName, "specularLightColor", 3, glm::value_ptr(light->m_specularColor));
    }

    for (const std::pair<std::string, glm::vec3>& pair : material->GetVec3Uniforms())
    {
        glm::vec3 value = pair.second;
        shaderManager->SetUniform(shaderName, pair.first, 3, glm::value_ptr(value));
    }

    for (const std::pair<std::string, glm::vec4>& pair : material->GetVec4Uniforms())
    {
        glm::vec4 value = pair.second;
        shaderManager->SetUniform(shaderName, pair.first, 4, glm::value_ptr(value));
    }

    for (const std::pair<std::string, Texture>& pair : material->GetTextureUniforms())
    {
        const Texture& texture = pair.second;
        int textureSlot = texture.m_slot;
        shaderManager->SetUniform(shaderName, pair.first, 1, &textureSlot);
    }

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

    glBindVertexArray(m_attributeVertexArray);
    PrepareShader(m_material, shaderManager, camera, light);
    int i = 0;

    for (const std::pair<std::string, Texture>& pair : m_material->GetTextureUniforms())
    {
        const Texture& texture = pair.second;
        glActiveTexture(GL_TEXTURE0 + texture.m_slot);
        glBindTexture(GL_TEXTURE_2D, m_textureIds[i]);
        i++;
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