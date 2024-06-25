#pragma once
#include "glutil.h"
#include <QImage>

namespace render::gl {
class RENDER_EXPORT Texture : public OpenGLBase {
public:
    Texture(const QColor& color, int width, int height, QImage::Format format = QImage::Format_RGBA8888);
    Texture(QString imagePath);
    Texture(const QImage& image);
    Texture(QImage&& image);
    virtual ~Texture();
    void destory();
    void setMipmapEnable(bool enable) { m_mipmapEnable = enable; }
    void setWrapMode(GLint wrapMode) { m_wrapMode = wrapMode; }
    void setFilterMode(GLint filterMode) { m_filterMode = filterMode; }
    GLuint textureId() { return m_textureId; }
    int width() { return m_width; }
    int height() { return m_height; }

protected:
    void genTexture(const QImage& image);
    QImage convertQImageFormatToGL(const QImage& image, GLuint& glForamt, bool& needConvert);

private:
    GLuint m_textureId = 0;
    int m_width = 0;
    int m_height = 0;
    GLint m_wrapMode = GL_CLAMP_TO_BORDER; // GL_REPEAT;
    GLint m_filterMode = GL_LINEAR;
    bool m_mipmapEnable = false;
};
} // namespace render::gl
