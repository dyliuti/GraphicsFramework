#include "vertexarrayobject.h"

void render::gl::VertexArrayObject::destory() {
    if(m_objectId != 0) {
        m_gl->glDeleteVertexArrays(1, &m_objectId);
        m_objectId = 0;
    }
}
