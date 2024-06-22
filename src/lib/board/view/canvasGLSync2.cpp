#include "CanvasGLSync2.h"
#include "opengl/videoframe.h"
#include "opengl/viewport.h"
#include <QDateTime>
#include <QDebug>
#include <QOpenGLTexture>
#include "opengl/shaderprogram.h"
#include "opengl/buffer.h"
#include "opengl/vertexarrayobject.h"

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec2 texCoord;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0f);\n"
"ourColor = color;\n"
"TexCoord = vec2(texCoord.x * 2,  (1.0 - texCoord.y) * 2);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"out vec4 color;\n"

"uniform float mixValue;\n"
"uniform sampler2D ourTexture1;\n"
"uniform sampler2D ourTexture2;\n"
"void main()\n"
"{\n"
"color = mix(texture(ourTexture1, TexCoord) * vec4(ourColor, 1.0f), texture(ourTexture2, TexCoord), mixValue);\n"
"}\n\0";

using namespace render::gl;
CanvasGLSync2::CanvasGLSync2(QWidget* parent)
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
        //throw std::runtime_error("context creation failed");
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

std::shared_ptr<VideoFrame> CanvasGLSync2::generateVideoFrame(int width, int height)
{
    auto texture = std::make_shared<render::gl::Texture>("");
//    GLuint textureId;
//    glGenTextures(1, &textureId);
//    texture->createNew();
//    qInfo() << "gl error: " << glGetError();
//    glBindTexture(GL_TEXTURE_2D, texture->textureId());
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//    glBindTexture(GL_TEXTURE_2D, 0);

    return std::make_shared<VideoFrame>(texture, width, height);
}

std::shared_ptr<VideoFrame> CanvasGLSync2::generateVideoFrame(int width, int height, QColor color)
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

    return videoFrame;
}

std::shared_ptr<VideoFrame> CanvasGLSync2::generateBackgroundVideoFrame()
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
    m_textureDrawer->drawTexture(videoFrame, viewPort, true);

    //    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //    glDeleteFramebuffers(1, &frameBuffer);

    return backgroundFrame;
}

std::unique_ptr<render::gl::Texture> s_texture;
GLuint VAO;
void CanvasGLSync2::initializeGL()
{
    qInfo() << "gl initializeGL: ";
    initializeOpenGLFunctions();
    m_textureDrawer = std::make_unique<render::gl::TextureDrawer>();
    m_program = std::make_unique<render::gl::ShaderProgram>();
    m_program->createProgram(QString("D:/Git/OpenGL/Lesson1/Shaders/Textures.vs"), QString("D:/Git/OpenGL/Lesson1/Shaders/Textures.frag"));

    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
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
    s_texture = std::make_unique<render::gl::Texture>("D:/Git/OpenGL/Lesson1/Image/container.jpg");
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
    glBindTexture(GL_TEXTURE_2D, s_texture->textureId());

    // Activate shader
    m_program->useProgram();

    // Draw container
    glBindVertexArray(m_vertexArray->objectId());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

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
