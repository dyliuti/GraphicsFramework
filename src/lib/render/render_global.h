#ifndef RENDER_GLOBAL_H
#define RENDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RENDER_LIBRARY)
#  define RENDER_EXPORT Q_DECL_EXPORT
#else
#  define RENDER_EXPORT Q_DECL_IMPORT
#endif

#endif // RENDER_GLOBAL_H
