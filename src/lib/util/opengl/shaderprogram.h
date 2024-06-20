#pragma once
#include "glutil.h"
#include <memory>

namespace render::gl {
class UTIL_EXPORT ShaderProgram : public OpenGLBase {
public:
    ShaderProgram() = default;
    ~ShaderProgram()
    {
        if (m_programId) {
            m_gl->glDeleteProgram(m_programId);
            m_programId = 0;
        }
    }
    bool createProgram(const char* vertex_shader, const char* fragment_shader);
    GLuint programId() const
    {
        return m_programId;
    }
    void useProgram()
    {
        m_gl->glUseProgram(m_programId);
    }

protected:
    GLuint loadShader(GLenum type, const char* source);

    bool checkGlShaderCompilation(const char* message, GLuint shader);

    bool checkGlProgramLink(const char* message, GLuint program);

private:
    GLuint m_programId = 0;
};
} // namespace render::gl
