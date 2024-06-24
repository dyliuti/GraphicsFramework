#ifndef PAINTER_RESIZABLEHANDLERECT_H
#define PAINTER_RESIZABLEHANDLERECT_H

#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include "handleitem.h"
#include "board_global.h"

BOARD_PAINTER_NAMESPACE_BEGIN
class ResizableHandleRect
{
public:
    ResizableHandleRect();
    virtual ~ ResizableHandleRect();

    virtual QRectF rectBounds() const = 0;
    virtual void setRectBounds(QRectF boundsRect) = 0;

    void drawHandlesIfNecessary();

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

    void setOwnerItem(QGraphicsItem *value);

private:
    void drawHandles();
    QRectF topleftHandleRect;
    QRectF topRightHandleRect;
    QRectF bottomRightHandleRect;
    QRectF bottomLeftHandleRect;

    QList<HandleItem * > handleList;
    bool handlesAddedToScene;
    QGraphicsItem * ownerItem;

};
BOARD_PAINTER_NAMESPACE_END

#endif // PAINTER_RESIZABLEHANDLERECT_H
