#pragma once
#include "glutil.h"
#include <memory>
#include <QMatrix4x4>

namespace render::gl {
class VertexArrayObject;
class ShaderProgram;
class UTIL_EXPORT TextureDrawer : public OpenGLBase {
public:
    TextureDrawer();
    ~TextureDrawer();
    void drawTexture(GLuint textureId);
    void setRotateMatrix(const QMatrix4x4& matrix) {m_rotateMatrix = matrix;}
private:
    std::unique_ptr<ShaderProgram> m_program;
    std::unique_ptr<render::gl::VertexArrayObject> m_vertexArray;
    QMatrix4x4 m_rotateMatrix;
};

} // namespace render::gl
