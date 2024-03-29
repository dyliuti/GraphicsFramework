﻿#include "statemachine.h"
#include "statebase.h"
#include "view/scene.h"
#include <QDebug>
BOARD_NAMESPACE_USE
StateMachine::StateMachine(Scene* scene)
    : m_commonData(std::make_shared<StateCommonData>())
    , m_scene(scene)
{
}

StateType StateMachine::getCurStateType()
{
    return m_curState ? m_curState->getStateType() : StateType::Undefined;
}

std::shared_ptr<StateBase> StateMachine::switchState(StateType type)
{
    if (m_curState && m_curState->getStateType() == type) {
        return nullptr;
    }
    auto it = m_stateMap.find(static_cast<StateType>(type));
    if (it == m_stateMap.end()) {
        return nullptr;
    }

    m_curState = it.value();
    qInfo() << "state type: " << (int)type;
    return m_curState;
}

void StateMachine::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_curState->mousePressEvent(event);
}

void StateMachine::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    m_curState->mouseMoveEvent(event);
}

void StateMachine::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_curState->mouseReleaseEvent(event);
}

void StateMachine::registState(StateType type, std::shared_ptr<StateBase> state)
{
    state->setStateType(type);
    state->setScene(m_scene);
    state->setSwitchFunc(std::bind(&StateMachine::switchState, this, std::placeholders::_1));

    m_stateMap[type] = state;
}

bool StateMachine::isCureentSelectType()
{
    auto type = m_curState ? m_curState->getStateType() : StateType::Undefined;
    return type == StateType::Select || type == StateType::BoxSelect;
}
