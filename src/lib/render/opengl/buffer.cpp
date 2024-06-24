#include "buffer.h"

render::gl::Buffer::Buffer() : OpenGLBase()
{
    m_gl->glGenBuffers(1, &m_bufferId);
}

void render::gl::Buffer::destory() {
    if(m_bufferId != 0) {
        m_gl->glDeleteBuffers(1, &m_bufferId);
        m_bufferId = 0;
    }
}

void VertexBuffer::setVertexAttribute(GLuint index, GLint size, int stride, int beginIndex)
{
    m_gl->glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(beginIndex * sizeof(GLfloat)));
    m_gl->glEnableVertexAttribArray(index);
}
