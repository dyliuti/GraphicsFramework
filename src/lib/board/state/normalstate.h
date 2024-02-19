//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_NORMALSTATE_H
#define BOARD_NORMALSTATE_H
#include "statebase.h"

BOARD_NAMESPACE_BEGIN
class NormalState : public StateBase {
public:
    using StateBase::StateBase;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};
BOARD_NAMESPACE_END
#endif // BOARD_NORMALSTATE_H
