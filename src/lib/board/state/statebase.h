//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_STATEBASE_H
#define BOARD_STATEBASE_H

#include "board_global.h"
#include "boarddefine.h"
#include <QGraphicsSceneMouseEvent>
#include <functional>

BOARD_NAMESPACE_BEGIN
class StateBase {
public:
    typedef std::shared_ptr<StateBase> ptr;
    virtual ~StateBase() = default;

    void setScene(Scene* scene) { m_scene = scene; };
    void setStateType(StateType type);
    StateType getStateType() const;
    void setSwitchFunc(std::function<std::shared_ptr<StateBase>(StateType)> func);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    //    virtual void mouseDoubleClickEvent(std::shared_ptr<MouseInfo> event);
    //    virtual void hoverEnterEvent(std::shared_ptr<HoverInfo> event);
    //    virtual void hoverLeaveEvent(std::shared_ptr<HoverInfo> event);
    //    virtual void hoverMoveEvent(std::shared_ptr<HoverInfo> event);
    //    virtual void leaveEvent(std::shared_ptr<MouseInfo> event);
    //    virtual void wheelEvent(std::shared_ptr<WheelInfo> event);
    //    virtual void contextMenuEvent(std::shared_ptr<MouseInfo> event);

protected:
    std::shared_ptr<StateBase> switchState(StateType type);

protected:
    StateType m_type;
    std::function<std::shared_ptr<StateBase>(StateType)> m_switchFunc;
    Scene* m_scene = nullptr;
};
BOARD_NAMESPACE_END
#endif // BOARD_STATEBASE_H
