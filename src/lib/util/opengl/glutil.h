#pragma once
#include "util_global.h"
#include <QOpenGLExtraFunctions>

class UTIL_EXPORT OpenGLBase {
public:
    OpenGLBase()
    {
        m_gl = QOpenGLContext::currentContext()->extraFunctions();
    }

protected:
    QOpenGLExtraFunctions* m_gl = nullptr;
};
