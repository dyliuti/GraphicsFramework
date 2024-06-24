#pragma once
#include "glutil.h"
#include <QMatrix4x4>
#include <memory>

namespace render::gl {
class VertexArrayObject;
class ShaderProgram;
class RENDER_EXPORT TextureDrawer : public OpenGLBase {
public:
    TextureDrawer();
    ~TextureDrawer();
    void drawTexture(GLuint textureId);
    void setRotateMatrix(const QMatrix4x4& matrix);

private:
    std::unique_ptr<ShaderProgram> m_program;
    std::unique_ptr<render::gl::VertexArrayObject> m_vertexArray;
    QMatrix4x4 m_rotateMatrix;
};

} // namespace render::gl
