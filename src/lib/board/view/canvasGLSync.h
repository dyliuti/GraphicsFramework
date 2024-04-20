//
// Created by yanminwei on 2024/4/20.
//

#ifndef CANVAS_GL_SYNC_H
#define CANVAS_GL_SYNC_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "renderthread.h"
#include <QWidget>
#include <QTimer>
#include "board_global.h"

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
};
#endif //CANVAS_GL_SYNC_H
