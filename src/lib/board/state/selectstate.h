//
// Created by yanminwei on 2024/2/25.
//
#ifndef BOARD_SELECTSTATE_H
#define BOARD_SELECTSTATE_H
#include "drawstate.h"

BOARD_NAMESPACE_BEGIN
/*** select
 * 1. press到item -> select state（选中个数不会变）   :  box select state（选中个数清空）
 * 2. box select state 时设置选中区域，然后回1 press判断
 * 3. select state可能是单元移动可能是多选移动，移就行了
 ***/
class SelectState : public DrawState {
public:
    using DrawState::DrawState;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
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
