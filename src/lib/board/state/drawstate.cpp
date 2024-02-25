#include "drawstate.h"
#include <QDebug>

BOARD_NAMESPACE_USE
void DrawState::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_lastPoint = event->scenePos();
}
