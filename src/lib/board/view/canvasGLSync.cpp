
#include "CanvasGLSync.h"
// #include "gl/GL.h"
#include <QDateTime>
#include <QDebug>

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
        throw std::runtime_error("context creation failed");
    }

    m_surface.setFormat(m_glContext.format());
    m_surface.create();
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

void CanvasGLSync::initializeGL()
{
    initializeOpenGLFunctions();
}

void CanvasGLSync::paintGL()
{
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_SCISSOR_TEST);
    glScissor(100, 0, 50, 50);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
