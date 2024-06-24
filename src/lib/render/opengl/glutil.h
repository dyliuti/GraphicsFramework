#pragma once
#include "render_global.h"
#include <QOpenGLExtraFunctions>

class RENDER_EXPORT OpenGLBase {
public:
    OpenGLBase()
    {
        m_gl = QOpenGLContext::currentContext()->extraFunctions();
    }

protected:
    QOpenGLExtraFunctions* m_gl = nullptr;
};
