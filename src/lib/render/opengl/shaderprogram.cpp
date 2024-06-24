#include "shaderprogram.h"
#include "qdebug.h"
#include <QFile>
#include <QTextStream>

namespace render::gl {
ShaderProgram::~ShaderProgram()
{
    if (m_programId != 0) {
        m_gl->glDeleteProgram(m_programId);
        m_programId = 0;
    }
}

bool ShaderProgram::createProgram(const char* vertex_shader, const char* fragment_shader)
{
    GLuint vertex_shader_id = loadShader(GL_VERTEX_SHADER, vertex_shader);
    checkShaderCompilation("loadVertexShader", vertex_shader_id);
    GLuint fragment_shader_id = loadShader(GL_FRAGMENT_SHADER, fragment_shader);
    checkShaderCompilation("loadFragmentShader", fragment_shader_id);
    m_programId = m_gl->glCreateProgram();
    m_gl->glAttachShader(m_programId, vertex_shader_id);
    m_gl->glAttachShader(m_programId, fragment_shader_id);
    m_gl->glLinkProgram(m_programId);
    checkProgramLink("glLinkProgram", m_programId);
    m_gl->glDetachShader(m_programId, vertex_shader_id);
    m_gl->glDetachShader(m_programId, fragment_shader_id);
    m_gl->glDeleteShader(vertex_shader_id);
    m_gl->glDeleteShader(fragment_shader_id);

    return true;
}

bool ShaderProgram::createProgram(QString vertexFile, QString fragmentFile)
{
    QFile verFile(vertexFile);
    if (!verFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QFile fragFile(fragmentFile);
    if (!fragFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream verIn(&verFile);
    QTextStream fragIn(&fragFile);

    return createProgram(verIn.readAll().toLocal8Bit().data(), fragIn.readAll().toLocal8Bit().data());
}

bool ShaderProgram::checkShaderCompilation(const char* message, GLuint shader)
{
    int success;
    char infoLog[512];
    m_gl->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        int length = 0;
        m_gl->glGetShaderInfoLog(shader, 511, &length, infoLog);
        length = std::min(length, 511);
        infoLog[length] = '\0';
        qWarning() << "shader compilation error: " << message << infoLog;
#if DEBUG
        assert(false);
#endif
    }

    return success;
}

bool ShaderProgram::checkProgramLink(const char* message, GLuint program)
{
    int success;
    char infoLog[512];
    m_gl->glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        int length = 0;
        m_gl->glGetProgramInfoLog(program, 511, &length, infoLog);
        length = std::min(length, 511);
        infoLog[length] = '\0';
        qWarning() << "program link error: " << message << infoLog;
#if DEBUG
        assert(false);
#endif
    }

    return success;
}

GLuint ShaderProgram::loadShader(GLenum type, const char* source)
{
    GLuint shader = m_gl->glCreateShader(type);
    m_gl->glShaderSource(shader, 1, &source, nullptr);
    m_gl->glCompileShader(shader);

    return shader;
}
} // namespace render::gl
