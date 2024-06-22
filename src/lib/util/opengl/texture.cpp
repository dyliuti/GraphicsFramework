#include "texture.h"
#include <QDebug>

render::gl::Texture::Texture(QString imagePath)
    : OpenGLBase()
{
    auto image = QImage(imagePath);
    genTexture(image);
}

render::gl::Texture::Texture(const QImage &image)
    : OpenGLBase()
{
    genTexture(image);
}

render::gl::Texture::~Texture()
{
    release();
}

void render::gl::Texture::genTexture(const QImage &image)
{
    m_gl->glGenTextures(1, &m_textureId);
    m_gl->glBindTexture(GL_TEXTURE_2D, m_textureId);
    m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode);
    m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode);
    m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
    m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);

    qInfo() << "ori image format: " << image.format();
    GLuint glFormat;
    const auto& img = convertQImageFormatToGL(image, glFormat);
    qInfo() << "image gl format: " << glFormat << img.width() << img.height();
    m_gl->glTexImage2D(GL_TEXTURE_2D, 0, glFormat, image.width(), image.height(), 0, glFormat, GL_UNSIGNED_BYTE, img.bits());
    if(m_mipmapEnable) {
        m_gl->glGenerateMipmap(GL_TEXTURE_2D);
    }
    m_gl->glBindTexture(GL_TEXTURE_2D, 0);
}

QImage render::gl::Texture::convertQImageFormatToGL(const QImage &image, GLuint& glFormat) {
    switch (image.format()) {
    case QImage::Format_RGB32:
    //case QImage::Format_ARGB32:
    case QImage::Format_RGBA8888:
    case QImage::Format_RGBA8888_Premultiplied:
        glFormat = GL_RGBA;
        return std::move(image);
    case QImage::Format_RGB888:
        glFormat = GL_RGB;
        return std::move(image);
    default:
        glFormat = GL_RGBA;
        return image.convertToFormat(QImage::Format_RGBA8888);
    }
}
