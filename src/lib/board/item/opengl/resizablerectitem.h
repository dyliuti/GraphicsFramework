#ifndef OPENGL_RESIZABLERECTITEM_H
#define OPENGL_RESIZABLERECTITEM_H

#include "board_global.h"
#include "boarddefine.h"
#include "resizablehandlerect.h"
#include <QGraphicsRectItem>

BOARD_NAMESPACE_BEGIN
OPENGL_NAMESPACE_BEGIN
class ResizableRectItem : public QGraphicsRectItem, public ResizableHandleRect {
public:
    explicit ResizableRectItem();
    enum { Type = ResizableRectType };
    int type() const override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    // ResizableHandleRect interface
    QRectF rectBounds() const override;
    void setRectBounds(QRectF boundsRect) override;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
};

// Write
QDataStream& operator<<(QDataStream& out, const ResizableRectItem& mRect);
// Read
QDataStream& operator>>(QDataStream& in, ResizableRectItem& mRectItem);
OPENGL_NAMESPACE_END
BOARD_NAMESPACE_END

#endif // OPENGL_RESIZABLERECTITEM_H
