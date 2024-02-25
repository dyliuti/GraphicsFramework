//
// Created by yanminwei on 2024/2/25.
//
#ifndef BOARD_SELECTSTATE_H
#define BOARD_SELECTSTATE_H
#include "drawstate.h"

BOARD_NAMESPACE_BEGIN
class SelectState : public DrawState {
public:
    using DrawState::DrawState;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

class SingleSelectState : public DrawState {

public:
    using DrawState::DrawState;
    void setSelectItem(QGraphicsItem* item) { m_selectItem = item; }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QGraphicsItem* m_selectItem = nullptr;
};

class BoxSelectState : public DrawState {

public:
    using DrawState::DrawState;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QGraphicsRectItem* m_selectRegionItem = nullptr;
};
BOARD_NAMESPACE_END
#endif // BOARD_SELECTSTATE_H
