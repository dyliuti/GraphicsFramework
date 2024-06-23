#include "CanvasGLSync2.h"
#include "opengl/videoframe.h"
#include "opengl/viewport.h"
#include <QDateTime>
#include <QDebug>
#include <QOpenGLTexture>
#include "opengl/shaderprogram.h"
#include "opengl/buffer.h"
#include "opengl/vertexarrayobject.h"
#include "opengl/framebufferobject.h"

using namespace render::gl;
CanvasGLSync2::CanvasGLSync2(QWidget* parent)
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

CanvasGLSync2::~CanvasGLSync2()
{
    cleanup();
}

QSize CanvasGLSync2::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CanvasGLSync2::sizeHint() const
{
    return QSize(400, 400);
}

void CanvasGLSync2::cleanup()
{
    if (m_timer.isActive()) {
        m_timer.stop();
    }

    makeCurrent();

    doneCurrent();
}

std::shared_ptr<VideoFrame> CanvasGLSync2::generateVideoFrame(QString filePath)
{
    QImage image(filePath);
    qInfo() << "img size: " << image.width();
    auto texture = std::make_shared<render::gl::Texture>(image);

    return std::make_shared<VideoFrame>(texture, image.width(), image.height());
}

void CanvasGLSync2::initializeGL()
{
    qInfo() << "gl initializeGL: ";
    initializeOpenGLFunctions();
    m_textureDrawer = std::make_unique<render::gl::TextureDrawer>();
    m_program = std::make_unique<render::gl::ShaderProgram>();
    m_program->createProgram(QString("D:/Work/GraphicsFramework/resource/shader/model.vs"), QString("D:/Work/GraphicsFramework/resource/shader/model.frag"));

    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle top right Tri
        1, 2, 3  // Second Triangle bottom left Tri
    };
    m_vertexArray = std::make_unique<VertexArrayObject>();
    m_vertexArray->bind();

    auto elementBuffer = std::make_shared<ElementBuffer>();
    elementBuffer->bind();
    elementBuffer->write(indices, sizeof(indices));
    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->bind();
    vertexBuffer->write(vertices, sizeof(vertices));
    // Position attribute
    vertexBuffer->setVertexAttribute(0, 3, 8, 0);
    // Color attribute
    vertexBuffer->setVertexAttribute(1, 3, 8, 3);
    // TexCoord attribute
    vertexBuffer->setVertexAttribute(2, 2, 8, 6);

    m_vertexArray->appendBuffer(elementBuffer);
    m_vertexArray->appendBuffer(vertexBuffer);

    m_vertexArray->release();

    // Load and create a texture
    auto texture = std::make_shared<render::gl::Texture>("D:/Work/GraphicsFramework/resource/model/facemodel.png");
//    auto texture = std::make_shared<render::gl::Texture>(QColor(0, 0, 255), 720, 1280);
    m_offscreenFBO = std::make_unique<render::gl::FrameBufferObject>(texture);
    m_offscreenFBO->bind();
    m_offscreenFBO->attachTexture();
    m_offscreenFBO->release();
}

void CanvasGLSync2::paintGL()
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
    qInfo() << "111111 gen backgroun frame00";
//    if (!m_backgroundFrame) {
//        qInfo() << "111111 gen backgroun frame";
//        m_backgroundFrame = generateBackgroundVideoFrame();
//    }
    // m_backgroundFrame = generateVideoFrame(720, 1280, QColor());
    // m_textureDrawer->drawTexture(m_backgroundFrame, viewPort, false);

    // Bind Texture   在哪个bind前后都没关系
    glBindTexture(GL_TEXTURE_2D, m_offscreenFBO->texture());

    // Activate shader
    m_program->useProgram();

    // draw model
    m_vertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vertexArray->release();

    // Set up vertex data (and buffer(s)) and attribute pointers

    //    nvgBeginPath(m_vg);
    //    nvgRect(m_vg, 100, 100, 120, 30);
    //    nvgFillColor(m_vg, nvgRGBA(255, 192, 0, 255));
    //    nvgFill(m_vg);
}

void CanvasGLSync2::resizeEvent(QResizeEvent* event)
{
    //    update();
    QWidget::resizeEvent(event);
}
