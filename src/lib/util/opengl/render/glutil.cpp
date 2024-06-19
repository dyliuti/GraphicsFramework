//
// Created by xukong on 2022/3/11.
//

#include "glutil.h"
#include "middleware/logger/zsloggermacro.h"
NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {
const GLfloat kTexcoords[][8] = {
    {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f},
};

const GLfloat kVertices[][8] = {
    {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f},
};

GLenum CheckGlError(const char* message) {
    GLenum error = GL_NO_ERROR;

    for (GLenum e = glGetError(); e; e = glGetError()) {
        error = e;
        LOG_ERROR("after {}() glError (0x{:x})\n", message, error);
#if DEBUG
        assert(false);
#endif
    }

    return error;
}

bool CheckGlShaderCompilation(const char* message, GLuint shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        int length = 0;
        glGetShaderInfoLog(shader, 511, &length, infoLog);
        length = std::min(length, 511);
        infoLog[length] = '\0';
        LOG_ERROR("after {}() glError {}\n", message, infoLog);
#if DEBUG
        assert(false);
#endif
    }

    return success;
}

bool CheckGlProgramLink(const char* message, GLuint program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        int length = 0;
        glGetProgramInfoLog(program, 511, &length, infoLog);
        length = std::min(length, 511);
        infoLog[length] = '\0';
        LOG_ERROR("after {} glError {}\n", message, infoLog);
#if DEBUG
        assert(false);
#endif
    }

    return success;
}

static const GLfloat* GetVertexCoordWithMirrorAndVerticalFlip(bool mirror, bool vertical_flip) {
    return mirror ? (vertical_flip ? kVertices[3] : kVertices[1]) : (vertical_flip ? kVertices[2] : kVertices[0]);
}

void AdjustFrameToScreen(GLuint gl_program, uint32_t width, uint32_t height,
                         GLfloat* vertex_coord, GLfloat* texture_coord,
                         Transform transform, const ViewPort& viewport, bool render_to_texture, GLuint* vbos) {
    glUseProgram(gl_program);
    glViewport(viewport.positionX, viewport.positionY, viewport.width, viewport.height);
    if (render_to_texture) {
        transform.rotation = (360 - transform.rotation) % 360;
    }
    ApplyVertexCoordTransform(vertex_coord, width, height, transform, viewport);
    GetTextureCoordWithCropAndRotation(texture_coord, transform, render_to_texture);
    GLuint vertex_location = glGetAttribLocation(gl_program, "position");
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glVertexAttribPointer(vertex_location, 2, GL_FLOAT, GL_FALSE, 0, vertex_coord);
    glEnableVertexAttribArray(vertex_location);
    GLuint texture_location = glGetAttribLocation(gl_program, "in_texCoord");
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glVertexAttribPointer(texture_location, 2, GL_FLOAT, GL_FALSE, 0, texture_coord);
    glEnableVertexAttribArray(texture_location);
    GLuint flip_location = glGetUniformLocation(gl_program, "flip");
    glUniform1i(flip_location, render_to_texture ? 0 : 1);
}

void ApplyVertexCoordTransform(GLfloat* dest_vertices, uint32_t width, uint32_t height, Transform transform, const ViewPort& viewport) {
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

GLuint LoadShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

void GetTextureCoordWithCropAndRotation(GLfloat* texture_coord, Transform transform, bool render_to_texture) {
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
                     texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7]) = std::make_tuple(x0, y0, x1, y0, x0, y1, x1, y1);
            break;

        case 90:
            std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
                     texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7]) = std::make_tuple(x1, y0, x1, y1, x0, y0, x0, y1);
            break;

        case 180:
            std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
                     texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7]) = std::make_tuple(x1, y1, x0, y1, x1, y0, x0, y0);
            break;

        case 270:
            std::tie(texture_coord[0], texture_coord[1], texture_coord[2], texture_coord[3],
                     texture_coord[4], texture_coord[5], texture_coord[6], texture_coord[7]) = std::make_tuple(x0, y1, x0, y0, x1, y1, x1, y0);
            break;
    }
}

}  // namespace render::gl
NAMESPACE_MIDDLEWARE_END