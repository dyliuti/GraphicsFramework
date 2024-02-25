//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_PENSTATE_H
#define BOARD_PENSTATE_H
#include "drawstate.h"

BOARD_NAMESPACE_BEGIN
class PenState : public DrawState {
public:
    using DrawState::DrawState;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};
BOARD_NAMESPACE_END
#endif // BOARD_PENSTATE_H
