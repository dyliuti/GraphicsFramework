//
// Created by xukong on 2022/3/10.
//

#pragma once
#include <OpenGL/gl3.h>
#include <memory>
#include "middleware/common/macros.h"
NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {
class Texture {
   public:
    Texture() {}
    Texture(GLuint textureId, bool isOes = false)
        : m_textureId(textureId), m_isOes(isOes) {}
    Texture(GLuint textureId, std::shared_ptr<void> pixelbuffer)
        : m_textureId(textureId),
          m_isPixelbuffer(true),
          m_pixelbuffer(pixelbuffer) {}
    virtual ~Texture() {
        release();
    }

    operator GLuint&() {
        return m_textureId;
    }

    void createNew() {
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);
        m_textureId = textureId;
    }

    void setTextureId(GLuint textureId) {
        m_textureId = textureId;
        m_isExternal = true;
    }

    void release() {
        if (m_textureId != 0 && !m_isExternal) {
            glDeleteTextures(1, &m_textureId);
            m_textureId = 0;
        }
    }

    GLuint textureId() {
        return m_textureId;
    }

    bool isOes() {
        return m_isOes;
    }

    void* attachedPixelbuffer() {
        return m_pixelbuffer.get();
    }

    std::shared_ptr<void> pixelbuffer() {
        return m_pixelbuffer;
    }

   private:
    GLuint m_textureId = 0;
    bool m_isExternal = false;
    bool m_isOes = false;
    bool m_isPixelbuffer = false;
    std::shared_ptr<void> m_pixelbuffer;
};
}  // namespace render::gl

NAMESPACE_MIDDLEWARE_END