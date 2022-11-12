#pragma once

#include <GL/glew.h>
#include <string>

class Scene;
class ShaderManager;

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    virtual void Draw(Scene* scene);
    bool TakeScreenshot(const std::string& filepath, int width, int height) const;

public:
    GLenum m_polygonMode;
    GLenum m_culledFace;
    bool m_isCullingFace;

protected:
    ShaderManager* m_shaderManager;
};