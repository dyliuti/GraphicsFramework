//
// Created by yanminwei on 2024/2/4.
//
#ifndef BOARD_GLOBAL_H
#define BOARD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BOARD_LIBRARY)
#define BOARD_EXPORT Q_DECL_EXPORT
#else
#define BOARD_EXPORT Q_DECL_IMPORT
#endif

#define BOARD_NAMESPACE_BEGIN \
    namespace board {

#define BOARD_NAMESPACE_END \
    }

#define BOARD_NAMESPACE_USE \
    using namespace board;

#define BOARD_OPENGL_NAMESPACE_BEGIN \
    namespace board::opengl {

#define BOARD_OPENGL_NAMESPACE_END \
    }

#define BOARD_OPENGL_NAMESPACE_USE \
    using namespace board::opengl;

#define BOARD_PAINTER_NAMESPACE_BEGIN \
    namespace board::painter {

#define BOARD_PAINTER_NAMESPACE_END \
    }

#define BOARD_PAINTER_NAMESPACE_USE \
    using namespace board::painter;

#endif // BOARD_GLOBAL_H
