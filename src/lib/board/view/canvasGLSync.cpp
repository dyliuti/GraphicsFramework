#include "CanvasGLSync.h"
#include <QDebug>
#include "opengl/framebufferobject.h"

using namespace render::gl;
CanvasGLSync::CanvasGLSync(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    m_glContext.setFormat(format);
    if (!m_glContext.create()) {
        qInfo() << "gl context create error";
        assert(false);
    }

    m_offscreenSurface.setFormat(m_glContext.format());
    m_offscreenSurface.create();
}

CanvasGLSync::~CanvasGLSync()
{
    if (m_timer.isActive()) {
        m_timer.stop();
    }

    makeCurrent();

    doneCurrent();
}

QSize CanvasGLSync::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CanvasGLSync::sizeHint() const
{
    return QSize(400, 400);
}

void CanvasGLSync::initializeGL()
{
    qInfo() << "gl initializeGL: ";
    initializeOpenGLFunctions();
    m_textureDrawer = std::make_unique<render::gl::TextureDrawer>();

    // Load and create a texture
    auto texture = std::make_shared<render::gl::Texture>("D:/Work/GraphicsFramework/resource/model/facemodel.png");
    // auto texture = std::make_shared<render::gl::Texture>(QColor(0, 0, 255), 720, 1280);
    m_offscreenFBO = std::make_unique<render::gl::FrameBufferObject>(texture);
    m_offscreenFBO->bind();
    m_offscreenFBO->attachTexture();
    m_offscreenFBO->release();
}

void CanvasGLSync::paintGL()
{
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //    glEnable(GL_SCISSOR_TEST);
    //    glScissor(100, 0, 50, 50);
    //    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);

    m_textureDrawer->drawTexture(m_offscreenFBO->textureId());

    //    nvgBeginPath(m_vg);
    //    nvgRect(m_vg, 100, 100, 120, 30);
    //    nvgFillColor(m_vg, nvgRGBA(255, 192, 0, 255));
    //    nvgFill(m_vg);
}

void CanvasGLSync::resizeEvent(QResizeEvent* event)
{
    if(m_offscreenFBO) {
        glViewport(0, 0, width() * devicePixelRatioF(), height() * devicePixelRatioF());
    }
    QWidget::resizeEvent(event);
}
