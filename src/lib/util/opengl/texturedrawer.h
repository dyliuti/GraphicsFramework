#pragma once
#include "glutil.h"
#include "videoframe.h"
#include <memory>

namespace render::gl {
class VertexArrayObject;
class ShaderProgram;
class UTIL_EXPORT TextureDrawer : public OpenGLBase {
public:
    TextureDrawer();
    ~TextureDrawer();
    void drawTexture(GLuint textureId);

private:
    std::unique_ptr<ShaderProgram> m_program;
    std::unique_ptr<render::gl::VertexArrayObject> m_vertexArray;
};

} // namespace render::gl
