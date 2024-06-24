#ifndef PAINTER_RESIZABLERECTITEM_H
#define PAINTER_RESIZABLERECTITEM_H

#include <QGraphicsRectItem>
#include "resizablehandlerect.h"
#include "boarddefine.h"
#include "board_global.h"

BOARD_PAINTER_NAMESPACE_BEGIN
class ResizableRectItem : public QGraphicsRectItem, public ResizableHandleRect
{
public:
    explicit ResizableRectItem();
    enum {Type = ResizableRectType};
    int type() const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // ResizableHandleRect interface

    QRectF rectBounds() const override;
    void setRectBounds(QRectF boundsRect) override;

    // QGraphicsItem interface
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

};

//Write
QDataStream &operator<<(QDataStream &out,
                        const ResizableRectItem & mRect);
//Read
QDataStream &operator>>(QDataStream &in, ResizableRectItem & mRectItem);
BOARD_PAINTER_NAMESPACE_END

#endif // PAINTER_RESIZABLERECTITEM_H
