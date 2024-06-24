#include "canvasGL.h"
#include "fileutil.h"
#include "opengl/framebufferobject.h"
#include "opengl/texture.h"
#include "opengl/texturedrawer.h"
#include <QDateTime>
#include <QDebug>
#include <QMatrix4x4>
#include <QStandardPaths>
#include <QUrl>

using namespace render::gl;

CanvasGL::CanvasGL(QWidget* parent)
    : QOpenGLWidget(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &CanvasGL::onRenderCanvas);
}

CanvasGL::~CanvasGL()
{
    if (m_timer.isActive()) {
        m_timer.stop();
    }
    syncRunOnRenderThread([&] {
        m_offscreenFBO.reset();
        m_renderThread->dropAllTasks();
    });
    if (m_renderThread != nullptr) {
        m_renderThread->deleteLater();
        m_renderThread = nullptr;
    };

    makeCurrent();
    m_textureDrawer.reset();
    doneCurrent();
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
static void cleanImageData(void* data)
{
    free(data);
}

static int s_rot = 0;
void CanvasGL::grabImage()
{
    runOnRenderThread([&]() {
        auto texture = m_offscreenFBO->texture();
        GLubyte* pixels = (GLubyte*)malloc(texture->width() * texture->height() * sizeof(GLubyte) * 4);
        glReadPixels(0, 0, texture->width(), texture->height(), GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        QImage image(pixels, texture->width(), texture->height(), QImage::Format_RGBA8888, &cleanImageData);
        auto docDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/graphics";
        FileUtil::makePath(docDir);
        image.save(QString("%1/img%2.png").arg(docDir).arg(s_rot));
    });
}

void CanvasGL::onRenderCanvas()
{
    if (m_renderFunction && m_renderThread) {
        m_renderThread->runOnRenderThread(m_renderFunction, RenderThread::CanvasRender);
    }
}

void CanvasGL::setRenderFunction(std::function<void()> renderFunction)
{
    m_renderFunction = [this, renderFunc = renderFunction]() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_offscreenFBO->fboId());
        renderFunc();
        glFlush();
        QMetaObject::invokeMethod(this, "update");
    };
}

QSize CanvasGL::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CanvasGL::sizeHint() const
{
    return QSize(400, 400);
}

void CanvasGL::initializeGL()
{
    initializeOpenGLFunctions();
    context()->setFormat(QSurfaceFormat::defaultFormat());
    qInfo() << "surface format1: " << context()->format();
    m_textureDrawer = std::make_unique<TextureDrawer>();

    m_renderThread = new RenderThread(this);
    m_renderThread->syncRunOnRenderThread([&]() {
        auto texture = std::make_shared<render::gl::Texture>(m_texturePath);
        // auto texture = std::make_shared<render::gl::Texture>(QColor(0, 0, 255), 720, 1280);
        m_offscreenFBO = std::make_unique<render::gl::FrameBufferObject>(texture);
        m_offscreenFBO->bind();
        m_offscreenFBO->attachTexture();
        m_textureDrawer->drawTexture(texture->textureId());
        m_offscreenFBO->release();
    });

    setRenderFunction([&]() {
        s_rot++;
        glEnable(GL_SCISSOR_TEST);
        glScissor(100, 100, 50, 50);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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
    });

    if (!m_timer.isActive()) {
        m_timer.start(1000 / 30);
    }
}

void CanvasGL::paintGL()
{
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_DEPTH);
    QMatrix matrix;
    matrix.rotate((s_rot++) % 360);
    matrix.rotate(30);
    QMatrix4x4 rotateMatrix = QMatrix4x4(matrix);
    m_textureDrawer->setRotateMatrix(rotateMatrix);
    m_textureDrawer->drawTexture(m_offscreenFBO->textureId());
}

void CanvasGL::resizeEvent(QResizeEvent* event)
{
    // if use QWidget::resizeEvent(event) -> unexpected behavior
    QOpenGLWidget::resizeEvent(event);
}

void CanvasGL::mousePressEvent(QMouseEvent* event)
{
    grabImage();
    QOpenGLWidget::mousePressEvent(event);
}
