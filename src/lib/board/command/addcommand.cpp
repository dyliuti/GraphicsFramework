#include "addcommand.h"

BOARD_NAMESPACE_USE
void AddCommand::exec()
{
    redo();
}

void AddCommand::undo()
{
    if (m_param->item && m_param->scene) {
        m_param->scene->removeItem(m_param->item);
    }
}

void AddCommand::redo()
{
    if (m_param->item && m_param->scene) {
        m_param->scene->addItem(m_param->item);
    }
}
