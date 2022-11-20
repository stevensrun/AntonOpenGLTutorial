#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

struct GLFWwindow;
class BasicMesh;
class Mesh;
class Scene;

class Renderer
{
public:
    explicit Renderer(GLFWwindow* window);
    virtual ~Renderer();

    virtual void Draw(Scene* scene);
    bool TakeScreenshot(const std::string& filepath, int width, int height) const;

private:
    void DrawGizmos(Scene* scene);
    void DrawImGui();
    std::unordered_map<std::string, std::vector<const BasicMesh*>> CreateMeshShaderBatch(const std::vector<BasicMesh*>& meshes);
    std::unordered_map<std::string, std::vector<const Mesh*>> CreateNormalsShaderBatch(const std::vector<BasicMesh*>& meshes);

public:
    GLenum m_polygonMode;
    GLenum m_culledFace;
    bool m_isCullingFace;
    bool m_drawNormals;
};