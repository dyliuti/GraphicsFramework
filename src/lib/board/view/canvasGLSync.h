//
// Created by yanminwei on 2024/4/20.
//

#ifndef CANVAS_GL_SYNC_H
#define CANVAS_GL_SYNC_H

#include "board_global.h"
#include "opengl/glutil.h"
#include "opengl/texturedrawer.h"
#include "renderthread.h"
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

// #include "item/opengl/nanovg/nanovg.h"
// #include "item/opengl/nanovg/nanovg_gl.h"
struct VideoFrame;
class BOARD_EXPORT CanvasGLSync : public QOpenGLWidget, protected OpenGlFunction {
    Q_OBJECT
public:
    explicit CanvasGLSync(QWidget* parent = nullptr);
    virtual ~CanvasGLSync();

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
    // NVGcontext* m_vg = nullptr;

    std::unique_ptr<render::gl::TextureDrawer> m_textureDrawer;
    std::shared_ptr<VideoFrame> m_backgroundFrame;
    std::shared_ptr<VideoFrame> m_inputFrame;
    std::shared_ptr<VideoFrame> m_outputFrame;
};
#endif // CANVAS_GL_SYNC_H
