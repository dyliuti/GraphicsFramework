//
// Created by yanminwei on 2024/2/25.
//
#ifndef BOARD_SINGLESELECTSTATE_H
#define BOARD_SINGLESELECTSTATE_H
#include "drawstate.h"

BOARD_NAMESPACE_BEGIN
class SelectState : public DrawState {
public:
    using DrawState::DrawState;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    int m_pressX;
};

class SingleSelectState : public DrawState {
public:
    using DrawState::DrawState;

protected:
    int m_pressX;
};

class BoxSelectState : public DrawState {
public:
    using DrawState::DrawState;

protected:
    int m_pressX;
};
BOARD_NAMESPACE_END
#endif // BOARD_SINGLESELECTSTATE_H
