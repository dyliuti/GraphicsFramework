#ifndef BOARD_ICOMMANDCTRL_H
#define BOARD_COMMANDCTRL_H

#include "icommandctrl.h"

#include "boarddefine.h"
#include <QVector>

BOARD_NAMESPACE_BEGIN
class CommandCtrl : public ICommandCtrl {
    Q_OBJECT
public:
    ~CommandCtrl();
    void execUndoRedoCommand(std::shared_ptr<IUndoRedoCommand> command) override;
    void undo(int step, bool needCheckUndoDeleteCommand = true) override;
    void redo(int step) override;
    void deleteCommand(int index) override;
    QJsonObject getHistoryInfo() const;
    int getRedoCommandSize() const;
    int getUndoCommandSize() const;

protected:
    void clearRedoStack();
    void clearUndoStack();
    void undoDeleteCommand();

protected:
    QList<std::shared_ptr<IUndoRedoCommand>> m_undoCommandVector;
    QList<std::shared_ptr<IUndoRedoCommand>> m_redoCommandVector;
    std::shared_ptr<IUndoRedoCommand> m_deleteCommand;
};
BOARD_NAMESPACE_END

#endif // BOARD_ICOMMANDCTRL_H
