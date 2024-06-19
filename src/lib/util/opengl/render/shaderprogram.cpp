//
// Created by xukong on 2022/3/11.
//

#include "shaderprogram.h"

NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {
bool ShaderProgram::createProgram(const char* vertex_shader, const char* fragment_shader) {
    GLuint vertex_shader_id = gl::LoadShader(GL_VERTEX_SHADER, vertex_shader);
    gl::CheckGlShaderCompilation("LoadVertexShader", vertex_shader_id);
    GLuint fragment_shader_id = gl::LoadShader(GL_FRAGMENT_SHADER, fragment_shader);
    gl::CheckGlShaderCompilation("LoadFragmentShader", fragment_shader_id);
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertex_shader_id);
    glAttachShader(m_programId, fragment_shader_id);
    glLinkProgram(m_programId);
    gl::CheckGlProgramLink("glLinkProgram", m_programId);
    glDetachShader(m_programId, vertex_shader_id);
    glDetachShader(m_programId, fragment_shader_id);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    gl::CheckGlError("glDeleteShader");
    return true;
}

}  // namespace render::gl

NAMESPACE_MIDDLEWARE_END