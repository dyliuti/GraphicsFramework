#include "canvasGLSync.h"
#include "opengl/videoframe.h"
#include "opengl/viewport.h"
#include <QDateTime>
#include <QDebug>
#include <QOpenGLTexture>

using namespace render::gl;
CanvasGLSync::CanvasGLSync(QWidget* parent)
    : QOpenGLWidget(parent) /*,
       QOpenGLFunctions(&m_glContext)*/
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    m_glContext.setFormat(format);
    if (!m_glContext.create()) {
        qInfo() << "gl context create error";
        throw std::runtime_error("context creation failed");
    }

    m_offscreenSurface.setFormat(m_glContext.format());
    m_offscreenSurface.create();
}

CanvasGLSync::~CanvasGLSync()
{
    cleanup();
}

QSize CanvasGLSync::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CanvasGLSync::sizeHint() const
{
    return QSize(400, 400);
}

void CanvasGLSync::cleanup()
{
    if (m_timer.isActive()) {
        m_timer.stop();
    }

    makeCurrent();

    doneCurrent();
}

std::shared_ptr<VideoFrame> CanvasGLSync::generateVideoFrame(QString filePath)
{
    QImage image(filePath);
    //    uint32_t width = (image.width() + 0x01) & (~0x01);
    //    uint32_t height = (image.height() + 0x01) & (~0x01);
    //    image = image.scaled(width, height, Qt::KeepAspectRatio);
    qInfo() << "img size: " << image.width();
    auto qtexture = std::make_unique<QOpenGLTexture>(image);
    auto texId = qtexture->textureId();
    auto texture = std::make_shared<render::gl::Texture>(texId);
    //      std::shared_ptr<Texture> texturePtr(texture, [=](Texture* texture) {
    //          delete qtexture;
    //          delete texture;
    //      });

    return std::make_shared<VideoFrame>(nullptr, qtexture->width(), qtexture->height());
}

std::shared_ptr<VideoFrame> CanvasGLSync::generateVideoFrame(int width, int height)
{
    auto texture = std::make_shared<render::gl::Texture>();
    GLuint textureId;
    glGenTextures(1, &textureId);
    texture->createNew();
    qInfo() << "gl error: " << glGetError();
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    qInfo() << __FUNCTION__ << CheckGlError();
    return std::make_shared<VideoFrame>(texture, width, height);
}

std::shared_ptr<VideoFrame> CanvasGLSync::generateVideoFrame(int width, int height, QColor color)
{
    auto videoFrame = generateVideoFrame(width, height);
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videoFrame->texture->textureId(), 0);
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &frameBuffer);
    qInfo() << __FUNCTION__ << CheckGlError();
    return videoFrame;
}

std::shared_ptr<VideoFrame> CanvasGLSync::generateBackgroundVideoFrame()
{
    const int kWidth = 720;
    const int kHeight = 1280;
    auto videoFrame = generateVideoFrame("C:/Work/GraphicsFramework/resource/model/facemodel.png"); /*preview_background*/
    auto backgroundFrame = generateVideoFrame(kWidth, kHeight);

    //    GLuint frameBuffer;
    //    glGenFramebuffers(1, &frameBuffer);
    //    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, backgroundFrame->texture->textureId(), 0);
    ViewPort viewPort(backgroundFrame->width, backgroundFrame->height, DisplayLayout::kLayoutAspectFill);
    // m_textureDrawer->drawTexture(videoFrame, viewPort, true);

    //    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //    glDeleteFramebuffers(1, &frameBuffer);

    return backgroundFrame;
}

void CanvasGLSync::initializeGL()
{
    qInfo() << "gl initializeGL: ";
    initializeOpenGLFunctions();
    m_textureDrawer = std::make_unique<render::gl::TextureDrawer>();
}

void CanvasGLSync::paintGL()
{
    auto gl = QOpenGLContext::currentContext()->functions();
    gl->glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    gl->glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    gl->glClear(GL_COLOR_BUFFER_BIT);
    //    glEnable(GL_SCISSOR_TEST);
    //    glScissor(100, 0, 50, 50);
    //    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);

    ViewPort viewPort(size().width() * this->devicePixelRatio(), size().height() * this->devicePixelRatio(), DisplayLayout::kLayoutAspectFill);
    //    if (!m_backgroundFrame) {
    //        generateBackgroundVideoFrame();
    //    }
    qInfo() << "111111 gen backgroun frame00";
    if (!m_backgroundFrame) {
        qInfo() << "111111 gen backgroun frame";
        m_backgroundFrame = generateBackgroundVideoFrame();
        //        const int kWidth = 720;
        //        const int kHeight = 1280;
        //        auto videoFrame = generateVideoFrame("C:/Work/GraphicsFramework/resource/model/facemodel.png"); /*preview_background*/
        //        //  auto backgroundFrame = generateVideoFrame(kWidth, kHeight);

        //        auto texture = std::make_shared<render::gl::Texture>();
        //        GLuint textureId;
        // glGenTextures(1, &textureId);
        //         texture->createNew();
        //         qInfo() << "gl error: " << glGetError();
        //         glBindTexture(GL_TEXTURE_2D, texture->textureId());
        //         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kWidth, kHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        //         glBindTexture(GL_TEXTURE_2D, 0);
        //         qInfo() << __FUNCTION__ << CheckGlError();
        //         m_backgroundFrame = std::make_shared<VideoFrame>(texture, kWidth, kHeight);
    }
    // m_backgroundFrame = generateVideoFrame(720, 1280, QColor());
    // m_textureDrawer->drawTexture(m_backgroundFrame, viewPort, false);

    //    nvgBeginPath(m_vg);
    //    nvgRect(m_vg, 100, 100, 120, 30);
    //    nvgFillColor(m_vg, nvgRGBA(255, 192, 0, 255));
    //    nvgFill(m_vg);
}

void CanvasGLSync::resizeEvent(QResizeEvent* event)
{
    //    update();
    QWidget::resizeEvent(event);
}
