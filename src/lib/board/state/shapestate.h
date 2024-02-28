//
// Created by yanminwei on 2024/2/28.
//
#ifndef BOARD_SHAPESTATE_H
#define BOARD_SHAPESTATE_H
#include "drawstate.h"

BOARD_NAMESPACE_BEGIN
class RectangleState : public DrawState {
public:
    using DrawState::DrawState;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

class CircleState : public DrawState {
public:
    using DrawState::DrawState;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

BOARD_NAMESPACE_END
#endif // BOARD_SHAPESTATE_H
