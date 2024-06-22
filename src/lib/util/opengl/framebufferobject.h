#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H

#include "glutil.h"

namespace render::gl {
class Texture;
class UTIL_EXPORT FrameBufferObject : public OpenGLBase
{
public:
    FrameBufferObject(std::shared_ptr<Texture> texture);
    ~FrameBufferObject() {destory();}
    void bind() {m_gl->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);}
    void release() {m_gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);}
    void destory();
    void attachTexture();
    GLuint texture();

protected:


protected:
    GLuint m_framebufferId = 0;
    std::shared_ptr<Texture> m_texture;
};
}
#endif // FRAMEBUFFEROBJECT_H
