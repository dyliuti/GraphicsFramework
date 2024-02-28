#include "selectstate.h"
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "view/scene.h"

BOARD_NAMESPACE_USE
void SelectState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    const auto& dPos = event->scenePos() - m_lastPoint;
    m_lastPoint = event->scenePos();
    auto selectItems = m_scene->selectedItems();
    for (const auto& item : selectItems) {
        item->moveBy(dPos.x(), dPos.y());
    }
}

void SelectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
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
