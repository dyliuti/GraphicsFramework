//
// Created by xukong on 2022/3/11.
//

#pragma once
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gltypes.h>
#include <assert.h>
#include <memory>
#include "glutil.h"
#include "middleware/common/macros.h"

NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {
class ShaderProgram final {
   public:
    ShaderProgram() = default;
    ~ShaderProgram() {
        if (m_programId) {
            glDeleteProgram(m_programId);
            m_programId = 0;
        }
    }
    bool createProgram(const char* vertex_shader, const char* fragment_shader);
    GLuint programId() const {
        return m_programId;
    }
    void useProgram() {
        glUseProgram(m_programId);
    }

   private:
    GLuint m_programId = 0;
};
}  // namespace render::gl

NAMESPACE_MIDDLEWARE_END