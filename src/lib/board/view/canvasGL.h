//
// Created by yanminwei on 2024/2/29.
//

#ifndef CANVAS_GL_H
#define CANVAS_GL_H

#include "board_global.h"
#include "opengl/texturedrawer.h"
#include "renderthread.h"
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

struct VideoFrame;
// namespace render::gl {
// class TextureDrawer;
// }
class BOARD_EXPORT CanvasGL : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit CanvasGL(QWidget* parent = nullptr);
    virtual ~CanvasGL();
    void setRenderFunction(std::function<void()> renderFunction);
    void runOnRenderThread(std::function<void()> func);
    void syncRunOnRenderThread(std::function<void()> func);
    void renderCanvas();

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
    void generateBackgroundVideoFrame();

protected:
    QTimer m_timer;
    RenderThread* m_renderThread = nullptr;
    QOpenGLContext m_glContext;
    QOffscreenSurface m_surface;
    std::function<void()> m_renderFunction;
    unsigned int m_offscreenFramebuffer {};

    std::unique_ptr<render::gl::TextureDrawer> m_textureDrawer;
    std::shared_ptr<VideoFrame> m_backgroundFrame;
    std::shared_ptr<VideoFrame> m_inputFrame;
    std::shared_ptr<VideoFrame> m_outputFrame;
};
#endif // CANVAS_GL_H
