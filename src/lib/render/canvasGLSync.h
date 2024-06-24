//
// Created by yanminwei on 2024/4/20.
//

#ifndef CANVAS_GL_SYNC_H
#define CANVAS_GL_SYNC_H

#include "render_global.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QTimer>

struct VideoFrame;
namespace render::gl {
class FrameBufferObject;
class TextureDrawer;
class Texture;
}

class RENDER_EXPORT CanvasGLSync : public QOpenGLWidget, public QOpenGLExtraFunctions {
    Q_OBJECT
public:
    explicit CanvasGLSync(QWidget* parent = nullptr);
    virtual ~CanvasGLSync();
    void setTexturePath(QString path) { m_texturePath = path; }

protected:
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void initializeGL() override;
    void paintGL() override;
    void resizeEvent(QResizeEvent* event) override;

protected:
    QTimer m_timer;
    std::unique_ptr<render::gl::FrameBufferObject> m_offscreenFBO;
    QString m_texturePath;
    std::unique_ptr<render::gl::TextureDrawer> m_textureDrawer;
};
#endif // CANVAS_GL_SYNC_H
