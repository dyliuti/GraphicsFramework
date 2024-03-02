//
// Created by yanminwei on 2024/2/29.
//

#ifndef CANVAS_GL_H
#define CANVAS_GL_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "renderthread.h"
#include <QWidget>
#include <QTimer>
#include "board_global.h"

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

protected:
    QTimer m_timer;
    RenderThread* m_renderThread = nullptr;
    QOpenGLContext m_glContext;
    QOffscreenSurface m_surface;
    std::function<void()> m_renderFunction;
    unsigned int m_offscreenFramebuffer{};
};
#endif //CANVAS_GL_H
