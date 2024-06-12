
#include "canvasGL.h"
//#include "gl/GL.h"
#include <QDebug>
#include <QDateTime>

CanvasGL::CanvasGL(QWidget* parent)
    : QOpenGLWidget(parent)/*,
      QOpenGLFunctions(&m_glContext)*/ {
    connect(&m_timer, &QTimer::timeout, this, &CanvasGL::renderCanvas);

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

CanvasGL::~CanvasGL() {
    cleanup();
}

void CanvasGL::setRenderFunction(std::function<void()> renderFunction) {
    m_renderFunction = [this, func = renderFunction]() {
//        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
        glBindFramebuffer(GL_FRAMEBUFFER, m_offscreenFramebuffer);
        func();
        glFlush();
        QMetaObject::invokeMethod(this, "update");
    };
}

void CanvasGL::runOnRenderThread(std::function<void()> func) {
    if (m_renderThread) {
        m_renderThread->runOnRenderThread(func);
    }
}

void CanvasGL::syncRunOnRenderThread(std::function<void()> func) {
    if (m_renderThread) {
        m_renderThread->syncRunOnRenderThread(func);
    }
}

void CanvasGL::renderCanvas() {
    if (m_renderFunction && m_renderThread) {
        m_renderThread->runOnRenderThread(m_renderFunction, RenderThread::CanvasRender);
    }
}


//void CanvasGL::render() {

//}

QSize CanvasGL::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize CanvasGL::sizeHint() const {
    return QSize(400, 400);
}

void CanvasGL::cleanup() {
    if (m_timer.isActive()) {
        m_timer.stop();
    }
    syncRunOnRenderThread([&] {
        glDeleteFramebuffers(1, &m_offscreenFramebuffer);
        m_renderThread->dropAllTasks();
    });
    if (m_renderThread != nullptr) {
        m_renderThread->deleteLater();
        m_renderThread = nullptr;
    };

    makeCurrent();

    doneCurrent();
}

void CanvasGL::initializeGL() {
    initializeOpenGLFunctions();

    m_renderThread = new RenderThread(this);
    m_renderThread->syncRunOnRenderThread([&]() {
        glGenFramebuffers(1, &m_offscreenFramebuffer);
    });

    setRenderFunction([&]() {
//        auto now = std::chrono::system_clock::now();
//        auto duration = now.time_since_epoch();
//        uint64_t ptsInMs = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
//        if (!m_inputFrame || m_markVideoFrameInvalid) {
//            generateInputVideoFrame(m_modelImage);
//        }

//        if (!m_outputFrame) {
//            m_outputFrame = Utils::generateVideoFrame(m_inputFrame->width, m_inputFrame->height);
//        }
//        m_inputFrame->pts = ptsInMs - m_lastTime;
//        render(m_inputFrame, m_outputFrame);

//        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
//        glEnable(GL_BLEND);
//        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);

//        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
//        makeCurrent();
        qInfo() << __FUNCTION__ << "777777" << QDateTime::currentDateTime();
//        glClear(GL_COLOR_BUFFER_BIT);
//        // 绘制矩形
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        // func 内容
        glEnable(GL_SCISSOR_TEST);
        glScissor(50, 50, 100, 100);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_BLEND);
//        doneCurrent();
    });
}

void CanvasGL::paintGL() {
    if (!m_timer.isActive()) {
        m_timer.start(1000 / 30);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_SCISSOR_TEST);
    glScissor(100, 0, 50, 50);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

//    glDisable(GL_BLEND);
}

void CanvasGL::resizeEvent(QResizeEvent *event)
{
//    update();
    QWidget::resizeEvent(event);
}

