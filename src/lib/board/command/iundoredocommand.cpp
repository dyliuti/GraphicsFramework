#include "iundoredocommand.h"

BOARD_NAMESPACE_USE
IUndoRedoCommand::IUndoRedoCommand(IUndoRedoParam::ptr param)
    : m_param(param)
{
}

void IUndoRedoCommand::setCommandInfo(const CommandInfo& info)
{
    m_param->commandInfo = info;
}

const CommandInfo& IUndoRedoCommand::getCommandInfo() const
{
    return m_param->commandInfo;
}

bool IUndoRedoCommand::isValid() const
{
    return m_param->valid;
}

IUndoRedoParam::ptr IUndoRedoCommand::getParam()
{
    return m_param;
}

void GroupCommand::exec()
{
    redo();
}

void GroupCommand::undo()
{
    for (int i = m_commandVec.size() - 1; i >= 0; --i) {
        m_commandVec[i]->undo();
    }
}

void GroupCommand::redo()
{
    for (const auto& command : m_commandVec) {
        command->exec();
    }
}

void GroupCommand::appendCommand(std::shared_ptr<IUndoRedoCommand> command)
{
    m_commandVec.append(command);
}

void GroupCommand::insertCommand(int index, std::shared_ptr<IUndoRedoCommand> command)
{
    m_commandVec.insert(index, command);
}

void GroupCommand::eraseCommand(int index)
{
    m_commandVec.erase(m_commandVec.begin() + index);
}

void GroupCommand::clearCommands()
{
    m_commandVec.clear();
}

int GroupCommand::size()
{
    return m_commandVec.size();
}
