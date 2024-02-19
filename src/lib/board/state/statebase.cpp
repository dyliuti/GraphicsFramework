#include "statebase.h"

BOARD_NAMESPACE_USE
void StateBase::setStateType(StateType type)
{
    m_type = type;
}

StateType StateBase::getStateType() const
{
    return m_type;
}

void StateBase::setSwitchFunc(std::function<std::shared_ptr<StateBase>(StateType)> pFunc)
{
    m_switchFunc = pFunc;
}

std::shared_ptr<StateBase> StateBase::switchState(StateType type)
{
    return m_switchFunc(type);
}

void StateBase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event)
}

void StateBase::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event)
}

void StateBase::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event)
}
