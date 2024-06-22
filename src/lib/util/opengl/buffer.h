#ifndef BUFFER_H
#define BUFFER_H
#include "glutil.h"

namespace render::gl {
class UTIL_EXPORT Buffer : public OpenGLBase
{
public:
    Buffer();
    virtual ~Buffer() {destory();};
    virtual void bind() = 0;
    virtual void release() = 0;
    virtual void write(const void *data, int count) = 0;
    void destory();
    GLuint bufferId() {return m_bufferId;}

protected:
    GLuint m_bufferId = 0;
};
}

class UTIL_EXPORT ElementBuffer : public render::gl::Buffer {
public:
    using Buffer::Buffer;
    void bind() override {m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);}
    void release() override {m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);}
    void write(const void *data, int count) override {m_gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);}
};

class UTIL_EXPORT VertexBuffer : public render::gl::Buffer {
public:
    using Buffer::Buffer;
    void bind() override {m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);}
    void release() override {m_gl->glBindBuffer(GL_ARRAY_BUFFER, 0);}
    void write(const void *data, int count) override {m_gl->glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);}
    void setVertexAttribute(GLuint index, GLint size, int num, int beginIndex);
};
#endif // BUFFER_H
