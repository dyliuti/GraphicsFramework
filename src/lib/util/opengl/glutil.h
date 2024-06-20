#pragma once
#include "util_global.h"
#include <QOpenGLFunctions>
#include <memory>
// extern const GLfloat kTexcoords[][8];

// extern const GLfloat kVertices[][8];

class UTIL_EXPORT OpenGlFunction : public QOpenGLFunctions {
public:
    GLenum CheckGlError(const char* message = "");

    const GLfloat* GetVertexCoordWithMirrorAndVerticalFlip(bool mirror, bool vertical_flip);
};

class UTIL_EXPORT OpenGLBase {
public:
    OpenGLBase()
    {
        m_gl = QOpenGLContext::currentContext()->functions();
    }

protected:
    QOpenGLFunctions* m_gl;
};
