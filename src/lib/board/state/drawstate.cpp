#include "drawstate.h"

BOARD_NAMESPACE_USE
void DrawState::setItem(std::shared_ptr<QGraphicsItem> item)
{
    m_item = item;
}
