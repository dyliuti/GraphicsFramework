//
// Created by yanminwei on 2024/2/29.
//

#ifndef CANVAS_GL_H
#define CANVAS_GL_H

#include "render_global.h"
#include "renderthread.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

struct VideoFrame;
namespace render::gl {
class FrameBufferObject;
class TextureDrawer;
}

class RENDER_EXPORT CanvasGL : public QOpenGLWidget, public QOpenGLExtraFunctions {
    Q_OBJECT
public:
    explicit CanvasGL(QWidget* parent = nullptr);
    virtual ~CanvasGL();
    void setTexturePath(QString path) { m_texturePath = path; }

    void runOnRenderThread(std::function<void()> func);
    void syncRunOnRenderThread(std::function<void()> func);
    void grabImage();

protected slots:
    void onRenderCanvas();

protected:
    void setRenderFunction(std::function<void()> renderFunction);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void initializeGL() override;
    void paintGL() override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

protected:
    QTimer m_timer;
    RenderThread* m_renderThread = nullptr;
    std::function<void()> m_renderFunction;
    QString m_saveGrapResourceDir;

    QString m_texturePath;
    std::unique_ptr<render::gl::FrameBufferObject> m_offscreenFBO;
    std::unique_ptr<render::gl::TextureDrawer> m_textureDrawer;
};
#endif // CANVAS_GL_H
