#include "texturedrawer.h"
#include <QDebug>

namespace render::gl {

static const char* vertexShaderSourceCore = R"(
    #version 150 core
    precision highp float;
    in vec4 position;
    in vec2 in_texCoord;
    out vec2 v_texCoord;
    uniform int flip;
    void main() {
        gl_Position = position;
        v_texCoord = vec2(in_texCoord.x, flip == 1 ? (1.0 - in_texCoord.y) : in_texCoord.y);
    }
)";

static const char* fragmentShaderSourceCore = R"(
    #version 150 core
    precision highp float;
    in vec2 v_texCoord;
    uniform sampler2D texture0;
    uniform int inversePremultiplyAlpha;
    out vec4 fragColor;
    void main() {
        fragColor = texture(texture0, v_texCoord);
        fragColor.rgb = inversePremultiplyAlpha == 1 ? (fragColor.rgb * 1.0 / fragColor.a) : fragColor.rgb;
    }
)";

const GLfloat kTexcoords[][8] = {
    { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
};

const GLfloat kVertices[][8] = {
    { -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f },
    { -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f },
    { 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f },
};

static const GLfloat* GetVertexCoordWithMirrorAndVerticalFlip(bool mirror, bool vertical_flip)
{
    return mirror ? (vertical_flip ? kVertices[3] : kVertices[1]) : (vertical_flip ? kVertices[2] : kVertices[0]);
}

TextureDrawer::TextureDrawer()
    : OpenGLBase()
    , m_program(new ShaderProgram)
{
    m_program->createProgram(vertexShaderSourceCore, fragmentShaderSourceCore);
    m_program->useProgram();
    m_gl->glUniform1i(m_gl->glGetUniformLocation(m_program->programId(), "texture0"), 0);
    // m_vao.create();
    //  glGenVertexArrays(1, &m_vao);
    m_gl->glGenBuffers(2, m_vbos);
}
TextureDrawer::~TextureDrawer()
{
    m_gl->glDeleteBuffers(2, m_vbos);
    // m_vao.destroy();
    //  glDeleteVertexArrays(1, &m_vao);
}

void TextureDrawer::drawTexture(const std::shared_ptr<VideoFrame>& frame, const ViewPort& viewPort,
    bool renderToTexture, bool enableInversePremultiplyAlpha)
{
    if (frame == nullptr) {
        return;
    }
    GLfloat vertex_coord[8] = { 0 };
    GLfloat texture_coord[8] = { 0 };
    uint32_t width = frame->width;
    uint32_t height = frame->height;
    // m_vao.bind();
    //  glBindVertexArray(m_vao);
    AdjustFrameToScreen(m_program->programId(), width, height, vertex_coord, texture_coord,
        frame->transform, viewPort, renderToTexture, m_vbos);
    GLint location = m_gl->glGetUniformLocation(m_program->programId(), "inversePremultiplyAlpha");
    m_gl->glUniform1i(location, enableInversePremultiplyAlpha ? 1 : 0);
    m_gl->glActiveTexture(GL_TEXTURE0);
    m_gl->glBindTexture(GL_TEXTURE_2D, frame->texture->textureId());
    // qInfo() << "111111: " << (int)CheckGlError("TextureDrawer");
    m_gl->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // glBindVertexArray(0);
    // m_vao.release();
}

void TextureDrawer::AdjustFrameToScreen(GLuint gl_program, uint32_t transformed_width, uint32_t transformed_height, GLfloat* vertex_coord, GLfloat* texture_coord, Transform transform, const ViewPort& viewport, bool render_to_texture, GLuint* vbos)
{
    m_gl->glUseProgram(gl_program);
    m_gl->glViewport(viewport.positionX, viewport.positionY, viewport.width, viewport.height);
    if (render_to_texture) {
        transform.rotation = (360 - transform.rotation) % 360;
    }
    ApplyVertexCoordTransform(vertex_coord, transformed_width, transformed_width, transform, viewport);
    GetTextureCoordWithCropAndRotation(texture_coord, transform, render_to_texture);
    GLuint vertex_location = m_gl->glGetAttribLocation(gl_program, "position");
    m_gl->glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    m_gl->glVertexAttribPointer(vertex_location, 2, GL_FLOAT, GL_FALSE, 0, vertex_coord);
    m_gl->glEnableVertexAttribArray(vertex_location);
    GLuint texture_location = m_gl->glGetAttribLocation(gl_program, "in_texCoord");
    m_gl->glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    m_gl->glVertexAttribPointer(texture_location, 2, GL_FLOAT, GL_FALSE, 0, texture_coord);
    m_gl->glEnableVertexAttribArray(texture_location);
    GLuint flip_location = m_gl->glGetUniformLocation(gl_program, "flip");
    m_gl->glUniform1i(flip_location, render_to_texture ? 0 : 1);
}

void TextureDrawer::ApplyVertexCoordTransform(GLfloat* dest_vertices, uint32_t width, uint32_t height, Transform transform, const ViewPort& viewport)
{
    const GLfloat* vertices = GetVertexCoordWithMirrorAndVerticalFlip(transform.mirror, transform.verticalFlip);
    float ratio = 1.0f * (width * viewport.height) / (height * viewport.width);
    memcpy(dest_vertices, vertices, sizeof(GLfloat) * 8);

    switch (viewport.displayLayout) {
    case DisplayLayout::kLayoutFixWidth: {
        dest_vertices[1] = dest_vertices[1] / ratio;
        dest_vertices[3] = dest_vertices[3] / ratio;
        dest_vertices[5] = dest_vertices[5] / ratio;
        dest_vertices[7] = dest_vertices[7] / ratio;
        break;
    }

    case DisplayLayout::kLayoutFixHeight: {
        dest_vertices[0] = dest_vertices[0] * ratio;
        dest_vertices[2] = dest_vertices[2] * ratio;
        dest_vertices[4] = dest_vertices[4] * ratio;
        dest_vertices[6] = dest_vertices[6] * ratio;
        break;
    }

    case DisplayLayout::kLayoutAspectFill: {
        if (ratio > 1.0f) {
            dest_vertices[0] = dest_vertices[0] * ratio;
            dest_vertices[2] = dest_vertices[2] * ratio;
            dest_vertices[4] = dest_vertices[4] * ratio;
            dest_vertices[6] = dest_vertices[6] * ratio;
        } else {
            dest_vertices[1] = dest_vertices[1] / ratio;
            dest_vertices[3] = dest_vertices[3] / ratio;
            dest_vertices[5] = dest_vertices[5] / ratio;
            dest_vertices[7] = dest_vertices[7] / ratio;
        }

        break;
    }

    case DisplayLayout::kLayoutAspectFit:
    default: {
        if (ratio > 1.0f) {
            dest_vertices[1] = dest_vertices[1] / ratio;
            dest_vertices[3] = dest_vertices[3] / ratio;
            dest_vertices[5] = dest_vertices[5] / ratio;
            dest_vertices[7] = dest_vertices[7] / ratio;
        } else {
            dest_vertices[0] = dest_vertices[0] * ratio;
            dest_vertices[2] = dest_vertices[2] * ratio;
            dest_vertices[4] = dest_vertices[4] * ratio;
            dest_vertices[6] = dest_vertices[6] * ratio;
        }

        break;
    }
    }
}

void TextureDrawer::GetTextureCoordWithCropAndRotation(GLfloat* texture_coord, Transform transform, bool render_to_texture)
{
    float crop_x = transform.cropXFrac != 0 ? transform.cropXFrac : 0;
    float crop_y = transform.cropYFrac != 0 ? transform.cropYFrac : 0;
    float crop_w = transform.cropWidthFrac != 0 ? transform.cropWidthFrac : 1;
    float crop_h = transform.cropHeightFrac != 0 ? transform.cropHeightFrac : 1;
    float x0 = crop_x, x1 = x0 + crop_w;
    float y0 = render_to_texture ? (1 - crop_y - crop_h) : crop_y;
    float y1 = y0 + crop_h;

    switch (transform.rotation) {
    case 0:
        std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
            texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7])
            = std::make_tuple(x0, y0, x1, y0, x0, y1, x1, y1);
        break;

    case 90:
        std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
            texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7])
            = std::make_tuple(x1, y0, x1, y1, x0, y0, x0, y1);
        break;

    case 180:
        std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
            texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7])
            = std::make_tuple(x1, y1, x0, y1, x1, y0, x0, y0);
        break;

    case 270:
        std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
            texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7])
            = std::make_tuple(x0, y1, x0, y0, x1, y1, x1, y0);
        break;
    }
}
} // namespace render::gl
