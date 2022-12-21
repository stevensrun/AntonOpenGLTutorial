#pragma once

#include <GL/glew.h>
#include <memory>
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
    std::unordered_map<std::string, std::vector<std::shared_ptr<BasicMesh>>> CreateMeshShaderBatch(const std::vector<std::shared_ptr<BasicMesh>>& meshes);
    std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> CreateNormalsShaderBatch(const std::vector<std::shared_ptr<BasicMesh>>& meshes);

public:
    GLenum m_polygonMode;
    GLenum m_culledFace;
    bool m_isCullingFace;
    bool m_drawNormals;
};