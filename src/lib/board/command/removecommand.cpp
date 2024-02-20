#include "removecommand.h"

BOARD_NAMESPACE_USE
void RemoveCommand::exec()
{
    redo();
}

void RemoveCommand::undo()
{
    if (m_param->item && m_param->scene) {
        m_param->scene->addItem(m_param->item);
    }
}

void RemoveCommand::redo()
{
    if (m_param->item && m_param->scene) {
        m_param->scene->removeItem(m_param->item);
    }
}
