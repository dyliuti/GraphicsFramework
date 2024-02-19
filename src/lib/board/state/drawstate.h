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
    void setItem(std::shared_ptr<QGraphicsItem> item);
    template <class T>
    std::shared_ptr<T> getTypicalItem(std::shared_ptr<QGraphicsItem> item)
    {
        return std::dynamic_pointer_cast<T>(item);
    }

protected:
    std::shared_ptr<QGraphicsItem> m_item;
};
BOARD_NAMESPACE_END
#endif // BOARD_DRAWSTATE_H
