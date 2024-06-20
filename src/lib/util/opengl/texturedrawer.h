#pragma once
#include "glutil.h"
#include "shaderprogram.h"
#include "videoframe.h"
#include "viewport.h"
#include <QOpenGLVertexArrayObject>
#include <memory>

namespace render::gl {

class UTIL_EXPORT TextureDrawer : public OpenGLBase {
public:
    TextureDrawer();
    ~TextureDrawer();
    void drawTexture(const std::shared_ptr<VideoFrame>& frame, const ViewPort& viewPort, bool renderToTexture = false, bool enableInversePremultiplyAlpha = false);

private:
    void AdjustFrameToScreen(GLuint gl_program, uint32_t transformed_width, uint32_t transformed_height,
        GLfloat* vertex_coord, GLfloat* texture_coord,
        Transform transform, const ViewPort& viewport, bool render_to_texture, GLuint* vbos);
    void ApplyVertexCoordTransform(GLfloat* dest_vertices, uint32_t width, uint32_t height, Transform transform, const ViewPort& viewport);
    void GetTextureCoordWithCropAndRotation(GLfloat* texture_coord, Transform transform, bool render_to_texture);

private:
    std::unique_ptr<ShaderProgram> m_program;
    // GLuint m_vao = 0;
    QOpenGLVertexArrayObject m_vao;
    GLuint m_vbos[2] = { 0 };
};

} // namespace render::gl
