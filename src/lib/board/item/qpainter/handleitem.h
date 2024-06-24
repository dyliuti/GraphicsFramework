#ifndef PAINTER_HANDLEITEM_H
#define PAINTER_HANDLEITEM_H

#include <QGraphicsRectItem>
#include "board_global.h"

BOARD_PAINTER_NAMESPACE_BEGIN
class HandleItem : public QGraphicsRectItem
{
public:
    enum Position
    {
        TopLeft,
        //TopCenter,
        TopRight,
        //RightCenter,
        BottomRight,
       // BottomCenter,
        BottomLeft,
        //LeftCenter
    };
    explicit HandleItem(Position position);


    // QGraphicsItem interface
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Position handlePosition;
};
BOARD_PAINTER_NAMESPACE_END
#endif // HANDLEITEM_H
