#include "penstate.h"
#include <QGraphicsItemGroup>

BOARD_NAMESPACE_USE
static std::shared_ptr<QGraphicsItemGroup> s_lineGroup;

void PenState::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void PenState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (!s_lineGroup) {
        s_lineGroup = std::make_shared<QGraphicsItemGroup>();
        s_lineGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    }
}

void PenState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    s_lineGroup = nullptr;
    //    switchState(kAnimationNormalStateKey)->mouseReleaseEvent(event);
}
