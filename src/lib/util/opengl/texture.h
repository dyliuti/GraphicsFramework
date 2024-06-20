#pragma once
#include "glutil.h"
#include <cstdio>
#include <memory>

namespace render::gl {
class UTIL_EXPORT Texture : public OpenGLBase {
public:
    Texture()
        : OpenGLBase()
    {
    }
    Texture(GLuint textureId)
        : OpenGLBase()
        , m_textureId(textureId)
    {
    }

    virtual ~Texture()
    {
        release();
    }

    operator GLuint&()
    {
        return m_textureId;
    }

    GLuint textureId()
    {
        return m_textureId;
    }

    void createNew()
    {
        GLuint textureId;
        m_gl->glGenTextures(1, &textureId);
        m_gl->glBindTexture(GL_TEXTURE_2D, textureId);
        m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        m_gl->glBindTexture(GL_TEXTURE_2D, 0);
        m_textureId = textureId;
    }

    void release()
    {
        if (m_textureId != 0) {
            m_gl->glDeleteTextures(1, &m_textureId);
            m_textureId = 0;
        }
    }

private:
    GLuint m_textureId = 0;
};
} // namespace render::gl
