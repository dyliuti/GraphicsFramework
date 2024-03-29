﻿//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_STATEMACHINE_H
#define BOARD_STATEMACHINE_H
#include "board_global.h"
#include "boarddefine.h"

#include <QGraphicsSceneMouseEvent>
#include <QMap>

BOARD_NAMESPACE_BEGIN
class StateBase;
class StateCommonData;
class Scene;
class View;
enum class StateType;
class BOARD_EXPORT StateMachine {
public:
    StateMachine(Scene* scene);

    std::shared_ptr<StateCommonData> getCommonData() { return m_commonData; }
    std::shared_ptr<StateBase> getCurState() { return m_curState; }
    StateType getCurStateType();
    std::shared_ptr<StateBase> switchState(StateType type);
    void registState(StateType type, std::shared_ptr<StateBase> state);
    bool isCureentSelectType();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

protected:
    std::shared_ptr<StateBase> m_curState;
    std::shared_ptr<StateCommonData> m_commonData;
    QMap<StateType, std::shared_ptr<StateBase>> m_stateMap;
    View* m_view = nullptr;
    Scene* m_scene = nullptr;
};
BOARD_NAMESPACE_END
#endif // BOARD_STATEMACHINE_H
