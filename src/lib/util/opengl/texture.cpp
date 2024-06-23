#include "texture.h"
#include <QDebug>

render::gl::Texture::Texture(const QColor& color, int width, int height, QImage::Format format)
    : OpenGLBase()
{
    auto image = QImage(width, height, format);
    image.fill(color);
    m_width = image.width();
    m_height = image.height();
    genTexture(image);
}

render::gl::Texture::Texture(QString imagePath)
    : OpenGLBase()
{
    auto image = QImage(imagePath);
    m_width = image.width();
    m_height = image.height();
    genTexture(image);
}

render::gl::Texture::Texture(const QImage &image)
    : OpenGLBase(), m_width(image.width()), m_height(image.height())
{
    genTexture(image);
}

render::gl::Texture::Texture(QImage &&image)
    : OpenGLBase(), m_width(image.width()), m_height(image.height())
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
    bool converted = false;
    const auto& convertedImg = convertQImageFormatToGL(image, glFormat, converted);
    qInfo() << "image gl format: " << glFormat << (converted ? convertedImg.size() : image.size());
    auto size = converted ? convertedImg.size() : image.size();
    m_gl->glTexImage2D(GL_TEXTURE_2D, 0, glFormat, size.width(), size.height(), 0, glFormat, GL_UNSIGNED_BYTE, converted ? convertedImg.bits() : image.bits());
    if(m_mipmapEnable) {
        m_gl->glGenerateMipmap(GL_TEXTURE_2D);
    }
    m_gl->glBindTexture(GL_TEXTURE_2D, 0);
}

QImage render::gl::Texture::convertQImageFormatToGL(const QImage &image, GLuint& glFormat, bool& needConvert) {
    switch (image.format()) {
    case QImage::Format_RGB32: // kCGImageAlphaNoneSkipFirst | kCGBitmapByteOrder32Host
    case QImage::Format_RGBA8888: // kCGImageAlphaLast | kCGBitmapByteOrder32Big
    case QImage::Format_RGBA8888_Premultiplied: // kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big
        glFormat = GL_RGBA;
    case QImage::Format_RGB888:
        glFormat = GL_RGB;
    default:
        glFormat = GL_RGBA;
        needConvert = true;
        return image.convertToFormat(QImage::Format_RGBA8888);
    }
}
