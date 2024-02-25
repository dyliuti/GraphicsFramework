//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_DRAWSTATE_H
#define BOARD_DRAWSTATE_H

#include "statebase.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

BOARD_NAMESPACE_BEGIN
class DrawState : public StateBase {
public:
    using StateBase::StateBase;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    QPointF m_lastPoint;
};
BOARD_NAMESPACE_END
#endif // BOARD_DRAWSTATE_H
