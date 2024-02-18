#ifndef VIEW_H
#define VIEW_H

#include "board_global.h"
#include <QGraphicsView>

BOARD_NAMESPACE_BEGIN
class BOARD_EXPORT View : public QGraphicsView
{
public:
    View();

};
BOARD_NAMESPACE_END

#endif // VIEW_H
