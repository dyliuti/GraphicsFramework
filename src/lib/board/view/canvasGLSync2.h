//
// Created by yanminwei on 2024/4/20.
//

#ifndef CANVAS_GL_SYNC2_H
#define CANVAS_GL_SYNC2_H

#include "board_global.h"
#include "opengl/texturedrawer.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>
#include <QOffscreenSurface>

struct VideoFrame;
namespace render::gl {
    class ShaderProgram;
    class VertexArrayObject;
}

class BOARD_EXPORT CanvasGLSync2 : public QOpenGLWidget, protected QOpenGLExtraFunctions {
    Q_OBJECT
public:
    explicit CanvasGLSync2(QWidget* parent = nullptr);
    virtual ~CanvasGLSync2();

protected:
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void initializeGL() override;
    void paintGL() override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void cleanup();
    std::shared_ptr<VideoFrame> generateVideoFrame(QString filePath);
    std::shared_ptr<VideoFrame> generateVideoFrame(int width, int height);
    std::shared_ptr<VideoFrame> generateVideoFrame(int width, int height, QColor color);
    std::shared_ptr<VideoFrame> generateBackgroundVideoFrame();

protected:
    QTimer m_timer;
    QOpenGLContext m_glContext;
    QOffscreenSurface m_offscreenSurface;

    std::unique_ptr<render::gl::ShaderProgram> m_program;
    std::unique_ptr<render::gl::VertexArrayObject> m_vertexArray;

    std::unique_ptr<render::gl::TextureDrawer> m_textureDrawer;
    std::shared_ptr<VideoFrame> m_backgroundFrame;
    std::shared_ptr<VideoFrame> m_inputFrame;
    std::shared_ptr<VideoFrame> m_outputFrame;
};
#endif // CANVAS_GL_SYNC_H
