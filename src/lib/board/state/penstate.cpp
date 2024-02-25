#include "penstate.h"
#include <QDebug>
#include <QGraphicsItemGroup>

BOARD_NAMESPACE_USE
static QGraphicsItemGroup* s_lineGroup = nullptr;

void PenState::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qInfo() << "111111: " << __FUNCTION__;
}

void PenState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

    if (!s_lineGroup) {
        s_lineGroup = new QGraphicsItemGroup();
        s_lineGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

        m_lastPoint = m_commonData->pressStartPos;

        m_commonData->scene->addItem(s_lineGroup);
    }

    const auto& endPoint = event->scenePos();
    auto partLine = new QGraphicsLineItem(QLineF(m_lastPoint, endPoint));
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue); // 优化，不用每次都创建的，订阅画笔状态进行变更就行了
    partLine->setPen(pen);
    s_lineGroup->addToGroup(partLine);

    m_lastPoint = endPoint;
    qInfo() << "111111: " << __FUNCTION__;
}

void PenState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    qInfo() << "111111: " << __FUNCTION__;
    s_lineGroup = nullptr; // 不析构，只是指针置空
}
