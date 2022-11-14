#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

class Mesh;
class Scene;
class ShaderManager;

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    virtual void Draw(Scene* scene);
    bool TakeScreenshot(const std::string& filepath, int width, int height) const;

private:
    std::unordered_map<std::string, std::vector<const Mesh*>> CreateMeshShaderBatch(const std::vector<Mesh*>& meshes);
    std::unordered_map<std::string, std::vector<const Mesh*>> CreateNormalsShaderBatch(const std::vector<Mesh*>& meshes);

public:
    GLenum m_polygonMode;
    GLenum m_culledFace;
    bool m_isCullingFace;

private:
    ShaderManager* m_shaderManager;
};