#ifndef PREVIEWGLWIDGET_H
#define PREVIEWGLWIDGET_H
#include "canvasGL.h"
#include "canvasGLSync.h"

class PreviewGLWidget : public CanvasGL {
public:
    using CanvasGL::CanvasGL;
};

class PreviewGLSyncWidget : public CanvasGLSync {
public:
    using CanvasGLSync::CanvasGLSync;
};

#endif // PREVIEWGLWIDGET_H
