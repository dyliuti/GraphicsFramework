#include "selectstate.h"
#include <QGraphicsItemGroup>

BOARD_NAMESPACE_USE
static std::shared_ptr<QGraphicsItemGroup> s_lineGroup;

void SelectState::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void SelectState::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (!s_lineGroup) {
        s_lineGroup = std::make_shared<QGraphicsItemGroup>();
        s_lineGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    }
}

void SelectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    s_lineGroup = nullptr;
    //    switchState(kAnimationNormalStateKey)->mouseReleaseEvent(event);
}
