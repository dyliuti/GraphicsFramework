#ifndef OPENGL_RESIZABLEHANDLERECT_H
#define OPENGL_RESIZABLEHANDLERECT_H

#include "board_global.h"
#include "handleitem.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>

BOARD_NAMESPACE_BEGIN
OPENGL_NAMESPACE_BEGIN
class ResizableHandleRect {
public:
    ResizableHandleRect();
    virtual ~ResizableHandleRect();

    virtual QRectF rectBounds() const = 0;
    virtual void setRectBounds(QRectF boundsRect) = 0;

    void drawHandlesIfNecessary();

    //    QPixmap getPixmap() const;
    //    void setPixmap(const QPixmap& value);

    void setOwnerItem(QGraphicsItem* value);

private:
    void drawHandles();

private:
    QList<std::shared_ptr<HandleItem>> m_handleList;
    QGraphicsItem* m_ownerItem;
};
OPENGL_NAMESPACE_END
BOARD_NAMESPACE_END

#endif // OPENGL_RESIZABLEHANDLERECT_H
