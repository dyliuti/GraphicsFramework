#pragma once
#include "glutil.h"
#include <QMatrix2x2>
#include <memory>

namespace render::gl {
class VertexArrayObject;
class ShaderProgram;
class Texture;
class RENDER_EXPORT TextureDrawer : public OpenGLBase {
public:
    TextureDrawer();
    ~TextureDrawer();
    void drawTexture(std::shared_ptr<Texture> texture);
    void setTime(float time);

private:
    std::unique_ptr<ShaderProgram> m_program;
    std::unique_ptr<render::gl::VertexArrayObject> m_vertexArray;
    float m_time = 0;
};

} // namespace render::gl
