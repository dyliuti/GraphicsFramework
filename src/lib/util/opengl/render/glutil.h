//
// Created by xukong on 2022/3/11.
//

#pragma once
#include <OpenGL/gl3.h>
#include <memory>
#include "middleware/common/macros.h"
#include "middleware/models/videoframe.h"
#include "viewport.h"

NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {
extern const GLfloat kTexcoords[][8];

extern const GLfloat kVertices[][8];

GLenum CheckGlError(const char* message);

GLuint LoadShader(GLenum type, const char* source);

bool CheckGlShaderCompilation(const char* message, GLuint shader);

bool CheckGlProgramLink(const char* message, GLuint program);

void AdjustFrameToScreen(GLuint gl_program, uint32_t transformed_width, uint32_t transformed_height,
                         GLfloat* vertex_coord, GLfloat* texture_coord,
                         Transform transform, const ViewPort& viewport, bool render_to_texture, GLuint* vbos);

void ApplyVertexCoordTransform(GLfloat* dest_vertices, uint32_t width, uint32_t height, Transform transform, const ViewPort& viewport);

void GetTextureCoordWithCropAndRotation(GLfloat* texture_coord, Transform transform, bool render_to_texture);

}  // namespace render::gl
NAMESPACE_MIDDLEWARE_END