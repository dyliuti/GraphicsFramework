#ifndef BOARD_GLOBAL_H
#define BOARD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BOARD_LIBRARY)
#  define BOARD_EXPORT Q_DECL_EXPORT
#else
#  define BOARD_EXPORT Q_DECL_IMPORT
#endif

#define BOARD_NAMESPACE_BEGIN \
namespace Board {

#define BOARD_NAMESPACE_END \
}

#define BOARD_NAMESPACE_USE \
using namespace Board;

#define OPENGL_NAMESPACE_BEGIN \
namespace Opengl {

#define OPENGL_NAMESPACE_END \
}

#define OPENGL_NAMESPACE_USE \
using namespace Opengl;

#define PAINTER_NAMESPACE_BEGIN \
namespace Painter {

#define PAINTER_NAMESPACE_END \
}

#define PAINTER_NAMESPACE_USE \
using namespace Painter;

#endif // BOARD_GLOBAL_H
