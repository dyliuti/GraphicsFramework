//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_STATEMACHINE_H
#define BOARD_STATEMACHINE_H
#include "boarddefine.h"
#include <QGraphicsSceneMouseEvent>
#include <QMap>

BOARD_NAMESPACE_BEGIN

class StateBase;
class StateCommonData;
enum class StateType;
class StateMachine {
public:
    StateMachine();

    std::shared_ptr<StateCommonData> getCommonData() { return m_commonData; }
    StateType getCurStateType();
    std::shared_ptr<StateBase> switchState(StateType type);
    void registState(StateType type, std::shared_ptr<StateBase> state);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

protected:
    std::shared_ptr<StateBase> m_curState;
    std::shared_ptr<StateCommonData> m_commonData;
    QMap<StateType, std::shared_ptr<StateBase>> m_stateMap;
};
BOARD_NAMESPACE_END
#endif // BOARD_STATEMACHINE_H
