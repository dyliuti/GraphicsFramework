#include "canvasGL.h"

#include "opengl/videoframe.h"
#include "opengl/viewport.h"
#include <QDateTime>
#include <QDebug>
#include <QOpenGLTexture>
using namespace render::gl;

CanvasGL::CanvasGL(QWidget* parent)
    : QOpenGLWidget(parent)
{
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

    m_textureDrawer = std::make_unique<TextureDrawer>();
}

CanvasGL::~CanvasGL()
{
    cleanup();
}

void CanvasGL::setRenderFunction(std::function<void()> renderFunction)
{
    m_renderFunction = [this, func = renderFunction]() {
        //        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
        glBindFramebuffer(GL_FRAMEBUFFER, m_offscreenFramebuffer);
        func();
        glFlush();
        QMetaObject::invokeMethod(this, "update");
    };
}

void CanvasGL::runOnRenderThread(std::function<void()> func)
{
    if (m_renderThread) {
        m_renderThread->runOnRenderThread(func);
    }
}

void CanvasGL::syncRunOnRenderThread(std::function<void()> func)
{
    if (m_renderThread) {
        m_renderThread->syncRunOnRenderThread(func);
    }
}

void CanvasGL::renderCanvas()
{
    if (m_renderFunction && m_renderThread) {
        m_renderThread->runOnRenderThread(m_renderFunction, RenderThread::CanvasRender);
    }
}

// void CanvasGL::render() {

//}

QSize CanvasGL::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CanvasGL::sizeHint() const
{
    return QSize(400, 400);
}

void CanvasGL::cleanup()
{
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

std::shared_ptr<VideoFrame> CanvasGL::generateVideoFrame(QString filePath)
{
    QImage image(filePath);
    //    uint32_t width = (image.width() + 0x01) & (~0x01);
    //    uint32_t height = (image.height() + 0x01) & (~0x01);
    //    image = image.scaled(width, height, Qt::KeepAspectRatio);
    auto qtexture = std::make_unique<QOpenGLTexture>(image);
    auto texture = std::make_shared<render::gl::Texture>(qtexture->textureId());
    //    std::shared_ptr<Texture> texturePtr(texture, [=](Texture* texture) {
    //        delete qtexture;
    //        delete texture;
    //    });

    return std::make_shared<VideoFrame>(texture, qtexture->width(), qtexture->height());
}

std::shared_ptr<VideoFrame> CanvasGL::generateVideoFrame(int width, int height)
{
    using Texture = render::gl::Texture;
    auto texture = std::make_shared<Texture>();
    texture->createNew();
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    return std::make_shared<VideoFrame>(texture, width, height);
}

void CanvasGL::generateBackgroundVideoFrame()
{
    if (m_backgroundFrame) {
        return;
    }

    const int kWidth = 720;
    const int kHeight = 1280;
    auto videoFrame = generateVideoFrame("C:/Work/GraphicsFramework/resource/model/facemodel.png"); /*preview_background*/
    m_backgroundFrame = generateVideoFrame(kWidth, kHeight);

    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_backgroundFrame->texture->textureId(), 0);
    ViewPort viewPort(m_backgroundFrame->width, m_backgroundFrame->height, DisplayLayout::kLayoutAspectFill);
    m_textureDrawer->drawTexture(videoFrame, viewPort, true);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &frameBuffer);
}

void CanvasGL::initializeGL()
{
    initializeOpenGLFunctions();

    m_renderThread = new RenderThread(this);
    m_renderThread->syncRunOnRenderThread([&]() {
        glGenFramebuffers(1, &m_offscreenFramebuffer);
    });

    // m_outputFrame = generateVideoFrame(m_inputFrame->width, m_inputFrame->height);

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

void CanvasGL::paintGL()
{
    if (!m_timer.isActive()) {
        m_timer.start(1000 / 30);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ViewPort viewPort(size().width() * this->devicePixelRatio(), size().height() * this->devicePixelRatio(), DisplayLayout::kLayoutAspectFill);
    if (!m_backgroundFrame) {
        generateBackgroundVideoFrame();
    }
    m_textureDrawer->drawTexture(m_backgroundFrame, viewPort, false);
    //    glDisable(GL_DEPTH_TEST);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //    m_textureDrawer->drawTexture(m_outputFrame, viewPort, false);
    //    glDisable(GL_BLEND);

    //    glEnable(GL_SCISSOR_TEST);
    //    glScissor(100, 0, 50, 50);
    //    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

    //    glClearColor(0, 0, 0, 1);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glDisable(GL_DEPTH_TEST);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    //    glDisable(GL_BLEND);
}

void CanvasGL::resizeEvent(QResizeEvent* event)
{
    //    update();
    QWidget::resizeEvent(event);
}
