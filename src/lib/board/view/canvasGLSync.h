//
// Created by yanminwei on 2024/4/20.
//

#ifndef CANVAS_GL_SYNC_H
#define CANVAS_GL_SYNC_H

#include "board_global.h"

#include "renderthread.h"
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

#include "item/opengl/nanovg/nanovg.h"
#include "item/opengl/nanovg/nanovg_gl.h"
class BOARD_EXPORT CanvasGLSync : public QOpenGLWidget, protected QOpenGLFunctions {
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

protected:
    QTimer m_timer;
    QOpenGLContext m_glContext;
    QOffscreenSurface m_surface;
    NVGcontext* m_vg = nullptr;
};
#endif // CANVAS_GL_SYNC_H
