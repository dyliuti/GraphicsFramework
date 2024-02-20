#include "movecommand.h"

BOARD_NAMESPACE_USE
void MoveCommand::exec()
{
    redo();
}

void MoveCommand::undo()
{
    if (m_param->item) {
        m_param->item->setPos(getTypicalParam<MoveParam>()->oldPos);
    }
}

void MoveCommand::redo()
{
    if (m_param->item) {
        m_param->item->setPos(getTypicalParam<MoveParam>()->newPos);
    }
}
