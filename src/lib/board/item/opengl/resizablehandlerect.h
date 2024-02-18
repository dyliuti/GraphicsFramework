#ifndef OPENGL_RESIZABLEHANDLERECT_H
#define OPENGL_RESIZABLEHANDLERECT_H

#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include "handleitem.h"
#include "board_global.h"

BOARD_NAMESPACE_BEGIN
OPENGL_NAMESPACE_BEGIN
class ResizableHandleRect
{
public:
    ResizableHandleRect();
    virtual ~ ResizableHandleRect();

    virtual QRectF selectorFrameBounds() const = 0;
    virtual void setSelectorFrameBounds(QRectF boundsRect) = 0;

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
OPENGL_NAMESPACE_END
BOARD_NAMESPACE_END

#endif // OPENGL_RESIZABLEHANDLERECT_H
