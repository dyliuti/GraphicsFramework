#include "commandctrl.h"
#include "iundoredocommand.h"
#include <QJsonArray>
#include <QJsonObject>

BOARD_NAMESPACE_USE
CommandCtrl::~CommandCtrl()
{
    clearRedoStack();
    clearUndoStack();
}

void CommandCtrl::execUndoRedoCommand(std::shared_ptr<IUndoRedoCommand> command)
{
    if (command == nullptr) {
        return;
    }

    command->exec();
    if (command->isValid()) {
        clearRedoStack();
        m_undoCommandVector.push_back(command);
        emit sigAddCommand();
    } else {
        command->clear();
    }

    m_deleteCommand = nullptr;
}

void CommandCtrl::undo(int step, bool needCheckUndoDeleteCommand)
{
    if (m_deleteCommand != nullptr && needCheckUndoDeleteCommand) {
        undoDeleteCommand();
        return;
    }

    while (step > 0 && !m_undoCommandVector.isEmpty()) {
        const auto& command = m_undoCommandVector.takeLast();
        command->undo();

        m_redoCommandVector.push_back(command);
        --step;
    }

    if (step > 0) {
        m_deleteCommand = nullptr;
    }
}

void CommandCtrl::redo(int step)
{
    while (step > 0 && !m_redoCommandVector.isEmpty()) {
        const auto& command = m_redoCommandVector.takeLast();
        command->redo();

        m_undoCommandVector.push_back(command);
        --step;
    }

    if (step > 0) {
        m_deleteCommand = nullptr;
    }
}

void CommandCtrl::deleteCommand(int index)
{
    if (m_redoCommandVector.empty() && index == (getUndoCommandSize() - 1)) {
        auto undoCommand = m_undoCommandVector.takeLast();
        undoCommand->undo();
        return;
    }

    m_deleteCommand = m_undoCommandVector.takeLast();
    m_deleteCommand->undo();
    std::shared_ptr<IUndoRedoCommand> nextCommand = m_redoCommandVector.takeLast();

    auto groupCommand = std::dynamic_pointer_cast<GroupCommand>(nextCommand);
    if (groupCommand == nullptr) {
        groupCommand = std::make_shared<GroupCommand>(nextCommand->getParam());
        groupCommand->appendCommand(m_deleteCommand);
        groupCommand->appendCommand(nextCommand);
    } else {
        groupCommand->insertCommand(0, m_deleteCommand);
    }

    m_redoCommandVector.append(groupCommand);
}

QJsonObject CommandCtrl::getHistoryInfo() const
{
    QJsonObject res;
    QJsonArray historyArr;
    QJsonObject obj;
    for (int i = 0; i < m_undoCommandVector.size(); ++i) {
        const auto& commandInfo = m_undoCommandVector[i]->getCommandInfo();
        obj["name"] = commandInfo.commandName;
        obj["undo"] = true;
        historyArr.append(obj);
    }

    for (int i = m_redoCommandVector.size() - 1; i >= 0; --i) {
        const auto& commandInfo = m_redoCommandVector[i]->getCommandInfo();
        obj["name"] = commandInfo.commandName;
        obj["undo"] = false;
        historyArr.append(obj);
    }

    obj["name"] = QStringLiteral("新建工程");
    obj["undo"] = true;
    historyArr.insert(0, obj);

    res["histroy"] = historyArr;
    res["currentIndex"] = getUndoCommandSize() - 1;

    return res;
}

int CommandCtrl::getRedoCommandSize() const
{
    return m_redoCommandVector.size();
}

int CommandCtrl::getUndoCommandSize() const
{
    return m_undoCommandVector.size() + 1;
}

void CommandCtrl::clearRedoStack()
{
    if (m_redoCommandVector.empty()) {
        return;
    }

    m_redoCommandVector.clear();
}

void CommandCtrl::clearUndoStack()
{
    if (m_undoCommandVector.empty()) {
        return;
    }

    m_undoCommandVector.clear();
}

void CommandCtrl::undoDeleteCommand()
{
    if (m_deleteCommand != nullptr) {
        auto redoCommand = std::dynamic_pointer_cast<GroupCommand>(m_redoCommandVector.takeLast());
        if (redoCommand == nullptr) {
            assert(redoCommand != nullptr);
            return;
        }
        redoCommand->eraseCommand(0);
        m_redoCommandVector.append(redoCommand);
        m_deleteCommand->redo();
        m_undoCommandVector.append(m_deleteCommand);
        m_deleteCommand = nullptr;
    }
}
