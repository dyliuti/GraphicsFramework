#include "shapestate.h"
#include <QGraphicsRectItem>
#include "qmath.h"
#include "view/scene.h"

BOARD_NAMESPACE_USE
static QGraphicsRectItem* s_rectItem = nullptr;
void RectangleState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(!s_rectItem) {
        s_rectItem = new QGraphicsRectItem();
        s_rectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        m_scene->addItem(s_rectItem);
    }

    const auto& endPoint = event->scenePos();
    QRectF rect = QRectF(m_lastPoint, endPoint);
    s_rectItem->setRect(rect.normalized());
}

void RectangleState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    s_rectItem = nullptr;
}

static QGraphicsEllipseItem* s_circleItem = nullptr;
void CircleState::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!s_circleItem) {
        s_circleItem = new QGraphicsEllipseItem();
        s_circleItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        m_scene->addItem(s_circleItem);
    }

    const auto& endPoint = event->scenePos();
    auto disLine = endPoint - m_lastPoint;
    auto minLine = qMin(qFabs(disLine.x()), qFabs(disLine.y()));
    QRectF rect = QRectF(m_lastPoint, QPointF(m_lastPoint.x() + minLine * (disLine.x() > 0 ? 1 : -1), m_lastPoint.y()+minLine *(disLine.y() > 0 ? 1 : -1)));
    s_circleItem->setRect(rect.normalized());
}

void CircleState::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    s_circleItem = nullptr;
}
