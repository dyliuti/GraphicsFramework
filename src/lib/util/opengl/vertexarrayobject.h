#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H
#include "glutil.h"

namespace render::gl {
class Buffer;
class UTIL_EXPORT VertexArrayObject : public OpenGLBase
{
public:
    VertexArrayObject() {m_gl->glGenVertexArrays(1, &m_objectId);}
    ~VertexArrayObject() {destory();}
    void bind() {m_gl->glBindVertexArray(m_objectId);}
    void release() {m_gl->glBindVertexArray(0);}
    void destory();
    void appendBuffer(std::shared_ptr<Buffer> buffer) {m_buffers.push_back(buffer);}
    GLuint objectId() {return m_objectId;};

protected:
    GLuint m_objectId = 0;
    std::list<std::shared_ptr<Buffer>> m_buffers;
};
}
#endif // VERTEXARRAYOBJECT_H
