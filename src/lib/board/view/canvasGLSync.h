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
    class FrameBufferObject;
}
class BOARD_EXPORT CanvasGLSync : public QOpenGLWidget, protected QOpenGLExtraFunctions {
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

protected:
    QTimer m_timer;
    QOpenGLContext m_glContext;
    QOffscreenSurface m_offscreenSurface;

    std::unique_ptr<render::gl::FrameBufferObject> m_offscreenFBO;
    std::unique_ptr<render::gl::TextureDrawer> m_textureDrawer;
};
#endif // CANVAS_GL_SYNC_H
