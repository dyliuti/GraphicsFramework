#include "selectstate.h"
#include <QDebug>
#include <QGraphicsItemGroup>

BOARD_NAMESPACE_USE
void SelectState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
}

void SelectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
}

void SingleSelectState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    qInfo() << "111111: " << __FUNCTION__ << event->scenePos() << m_lastPoint;
    if (m_selectItem) {
        const auto& dPos = event->scenePos() - m_lastPoint;
        m_lastPoint = event->scenePos();
        m_selectItem->moveBy(dPos.x(), dPos.y());
    }
}

void SingleSelectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
}

void BoxSelectState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // 设置选择区域
    QRectF selectRegion = QRectF(m_lastPoint, event->scenePos());
    QPainterPath path;
    path.addRect(selectRegion);
    m_scene->setSelectionArea(path);
    // 绘制选择区域
    if (m_selectRegionItem == nullptr) {
        qInfo() << "111111: " << __FUNCTION__ << m_selectRegionItem;
        m_selectRegionItem = new QGraphicsRectItem();
        m_selectRegionItem->setBrush(QBrush(QColor(255, 0, 0, 50)));
        m_scene->addItem(m_selectRegionItem);
    }

    m_selectRegionItem->setRect(selectRegion.normalized());
}

void BoxSelectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_scene->removeItem(m_selectRegionItem);
    delete m_selectRegionItem;
    m_selectRegionItem = nullptr;
}
