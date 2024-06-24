#include "framebufferobject.h"
#include "texture.h"
#include <QDebug>

render::gl::FrameBufferObject::FrameBufferObject(std::shared_ptr<Texture> texture) : OpenGLBase(),
    m_texture(texture)
{
    m_gl->glGenFramebuffers(1, &m_framebufferId);
}

void render::gl::FrameBufferObject::destory()
{
    if(m_framebufferId != 0) {
        m_gl->glDeleteFramebuffers(1, &m_framebufferId);
    }
}

void render::gl::FrameBufferObject::attachTexture()
{
    m_gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->textureId(), 0);
}

GLuint render::gl::FrameBufferObject::textureId()
{
    return m_texture->textureId();
}

GLuint render::gl::FrameBufferObject::fboId()
{
    return m_framebufferId;
}
