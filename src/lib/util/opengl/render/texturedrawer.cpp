//
// Created by xukong on 2022/3/11.
//

#include "texturedrawer.h"

NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {

static const char* vertexShaderSourceCore = R"(
  #version 150
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
  #version 150
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

TextureDrawer::TextureDrawer(bool isCore)
    : m_program(new ShaderProgram) {
    m_program->createProgram(vertexShaderSourceCore, fragmentShaderSourceCore);
    m_program->useProgram();
    glUniform1i(glGetUniformLocation(m_program->programId(), "texture0"), 0);
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(2, m_vbos);
}
TextureDrawer::~TextureDrawer() {
    glDeleteBuffers(2, m_vbos);
    glDeleteVertexArrays(1, &m_vao);
}

void TextureDrawer::drawTexture(const std::shared_ptr<VideoFrame>& frame, const ViewPort& viewPort,
                                bool renderToTexture, bool enableInversePremultiplyAlpha) {
    if (frame == nullptr) {
        return;
    }
    GLfloat vertex_coord[8] = {0};
    GLfloat texture_coord[8] = {0};
    uint32_t width = frame->width;
    uint32_t height = frame->height;
    glBindVertexArray(m_vao);
    gl::AdjustFrameToScreen(m_program->programId(), width, height, vertex_coord, texture_coord,
                            frame->transform, viewPort, renderToTexture, m_vbos);
    GLint location = glGetUniformLocation(m_program->programId(), "inversePremultiplyAlpha");
    glUniform1i(location, enableInversePremultiplyAlpha ? 1 : 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frame->texture->textureId());
    CheckGlError("TextureDrawer");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

}  // namespace render::gl

NAMESPACE_MIDDLEWARE_END
